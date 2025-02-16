#include "includs.h"

float EaseInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : 1.0f - powf(-2.0f * t + 2.0f, 2) / 2.0f;
}

Vector3 LerpVector3(Vector3 start, Vector3 end, float t) {
    Vector3 result;
    result.x = start.x + (end.x - start.x) * t;
    result.y = start.y + (end.y - start.y) * t;
    result.z = start.z + (end.z - start.z) * t;
    return result;
}

int main(void) {
    InitAudioDevice();
    MainMenu();
    const int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Game");
    InitWindow(screenWidth, screenHeight, "Main Menu");

    // Load music
    Music Main_music = LoadMusicStream("resources/music/main.mp3");  
    
    // Play the music
    PlayMusicStream(Main_music );
    SetMusicVolume(Main_music, 1.0f);

    bool isFullscreen = false;

    Font interFont = LoadFont("resources/fonts/Inter-Regular.ttf");
    SetTextureFilter(interFont.texture, TEXTURE_FILTER_BILINEAR);

    Camera3D cam1 = { 0 };
    cam1.position = (Vector3){ 80.0f, 55.0f, 70.0f };
    cam1.target   = (Vector3){ -15.0f, 0.0f, 10.0f };
    cam1.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
    cam1.fovy     = 65.0f;
    cam1.projection = CAMERA_PERSPECTIVE;

    Camera3D cam2 = { 0 };
    cam2.position = (Vector3){ 55.0f, 55.0f, 0.0f };
    cam2.target   = (Vector3){ -17.0f, 0.0f, -15.0f };
    cam2.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
    cam2.fovy     = 75.0f;
    cam2.projection = CAMERA_PERSPECTIVE;

    Camera3D camera = cam1;

    bool animating = false;
    bool camState = false;
    float t = 0.0f;
    const float transitionDuration = 1.2f;

    Rectangle buttonRect = { 20, 20, 200, 40 };
    Rectangle pauseButton = { 20, 70, 200, 40 };
    bool paused = false;

    Model bgModel = LoadModel("resources/models/Castle_no_walls.glb");
    Model wallModel = LoadModel("resources/models/new_new_wall.glb");

    Shader shader = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");
    for (int i = 0; i < bgModel.materialCount; i++) {
        bgModel.materials[i].shader = shader;
    }
    for (int i = 0; i < wallModel.materialCount; i++) {
        wallModel.materials[i].shader = shader;
    }

    Light light = CreateLight((Vector3){ -63.0f, 90.0f, 135.0f }, (Color){ 255, 214, 170, 255}, 0.5f);

    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    LoadNPCModel();
    LoadTowerModel(); 
    Tower *towers = NULL;
    int towerCount = 0;
    Arrow arrows[MAX_ARROWS] = { 0 };
    int currentArrowIndex = 0;

    SetTargetFPS(300);

    bool shopMenuOpen = false;
    int wallHP = 440, maxWallHP = 2000;
    int defenderLevel = 0, maxDefenderLevel = 100;

    Vector3 goldCubePos = { -8.0f, 8.0f, -25.0f };
    float goldCubeSize = 42.0f;

    // MOB Waves
    int currentNPCCount = 5;
    float spawnTimer = 0.0f;
    float miniWaveTimer = 0.0f;
    float waveTimer = 0.0f;
    float waveInterval = 20.0f;
    int waveNumber = 1; 

    while (!WindowShouldClose()) {
        UpdateMusicStream(Main_music);

        float deltaTime = GetFrameTime();
        Vector2 mousePoint = GetMousePosition();
        mousePoint.x *= (float)screenWidth / GetRenderWidth();
        mousePoint.y *= (float)screenHeight / GetRenderHeight();

        if (IsKeyPressed(KEY_F)) {
            isFullscreen = !isFullscreen;
            if (isFullscreen) {
                ToggleFullscreen();
            } else {
                SetWindowSize(screenWidth, screenHeight);
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, pauseButton)) {
            paused = !paused;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (shopMenuOpen) {
                Rectangle shopRect = { (float)(screenWidth - 300), 0, 300, screenHeight };
                if (!CheckCollisionPointRec(mousePoint, shopRect)) {
                    shopMenuOpen = false;
                }
            } 
            else {
                Ray ray = GetMouseRay(mousePoint, camera);
                if (CheckGoldCubeCollision(ray, goldCubePos, goldCubeSize)) {
                    shopMenuOpen = true;
                }
            }
        }

        // Обработка переключения камеры по кнопке
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, buttonRect) && !animating) {
            animating = true;
            t = 0.0f;
            camState = !camState;
        }

        if (animating) {
            t += deltaTime / transitionDuration;
            if (t >= 1.0f) { t = 1.0f; animating = false; }
            float smoothT = EaseInOutQuad(t);
            if (camState) {
                camera.position = LerpVector3(cam1.position, cam2.position, smoothT);
                camera.target   = LerpVector3(cam1.target, cam2.target, smoothT);
                camera.up       = LerpVector3(cam1.up, cam2.up, smoothT);
                camera.fovy     = cam1.fovy + (cam2.fovy - cam1.fovy) * smoothT;
            } else {
                camera.position = LerpVector3(cam2.position, cam1.position, smoothT);
                camera.target   = LerpVector3(cam2.target, cam1.target, smoothT);
                camera.up       = LerpVector3(cam2.up, cam1.up, smoothT);
                camera.fovy     = cam2.fovy + (cam1.fovy - cam2.fovy) * smoothT;
            }
        }

        if (!paused) {
            // Обновление волн
            wawes(&spawnTimer, &miniWaveTimer, &waveTimer, waveInterval, &waveNumber, &currentNPCCount);

            HideCursor();
            
            if (wallDestroyed) {
                // Обновление логики башен и стрел
                for (int i = 0; i < towerCount; ++i) {
                    towers[i].arrowTimer += GetFrameTime();
                    if (towers[i].arrowTimer >= FIRERATE - (defenderLevel*0.2f)) {  
                        towers[i].arrowTimer = 0.0f;  // Сброс таймера
                        LaunchArrow(&towers[i], &arrows[currentArrowIndex], npcs, npcCount);
                        currentArrowIndex = (currentArrowIndex + 1) % MAX_ARROWS;
                    }
                }
            }
            // Обновляем все стрелы
            for (int i = 0; i < MAX_ARROWS; i++){
                UpdateArrow(&arrows[i], deltaTime);
                CheckArrowCollisionWithNPCs(&arrows[i], npcs, npcCount);
            }

            UpdateLightShader(light, shader, camera);
        }

        BeginDrawing();
            ClearBackground(BLUE);

            BeginMode3D(camera);
                for (int i = 0; i < npcCount; i++) {
                    DrawNPC(&npcs[i]);
                }
                // for (int i = 0; i < towerCount; i++) {
                //     //DrawTower(&towers[i]);
                // }
                DrawFPS(10, 10);
                BeginShaderMode(shader);
                    if (wallDestroyed)
                        DrawModel(wallModel, (Vector3){0.0f, 1.0f, -1.0f}, 1.0f, WHITE);
                    DrawModel(bgModel, (Vector3){0.0f, 1.0f, 0.0f}, 1.0f, WHITE);
                EndShaderMode();

                if (wallDestroyed) {
                    // Отрисовка стрел
                    for (int i = 0; i < MAX_ARROWS; i++) {
                        DrawArrow(arrows[i]);
                    }
                    for (int i = 0; i < towerCount; ++i) {
                        DrawTower(&towers[i]);
                    }
                }

                DrawGoldCube(goldCubePos, goldCubeSize);
            EndMode3D();

            DrawRectangleRec(buttonRect, LIGHTGRAY);
            DrawText("Toggle Camera", buttonRect.x + 10, buttonRect.y + 10, 20, BLACK);
            DrawRectangleRec(pauseButton, LIGHTGRAY); // Отрисовка кнопки паузы
            DrawText(paused ? "Unpause" : "Pause", pauseButton.x + 10, pauseButton.y + 10, 20, BLACK);

            {
                int hpBarWidth = 500;
                int hpBarHeight = 50;
                int hpBarX = screenWidth / 2 - hpBarWidth / 2;
                int hpBarY = 20;

                float roundness = 0.3f;
                int segments = 10;
    
                Rectangle barRect = { (float)hpBarX, (float)hpBarY, (float)hpBarWidth, (float)hpBarHeight };
    
                DrawRectangleRounded(barRect, roundness, segments, DARKGRAY);
    

                float hpPercent = (float)wall.health / 2000.0f;
                int filledWidth = (int)(hpBarWidth * hpPercent);
                Rectangle filledRect = { (float)hpBarX, (float)hpBarY, (float)filledWidth, (float)hpBarHeight };
    
                Color darkMaroon = (Color){100, 0, 0, 255}; // можно настроить по вкусу
                DrawRectangleRounded(filledRect, roundness, segments, darkMaroon);

                DrawRectangleRoundedLines(barRect, roundness, segments, BLACK);
    
                char hpText[50];
                sprintf(hpText, "HP: %d / %d", wall.health, 2000);
                int textSize = 20;
                int textWidth = MeasureText(hpText, textSize);
                DrawText(hpText, hpBarX + (hpBarWidth - textWidth) / 2, hpBarY + (hpBarHeight - textSize) / 2, textSize, WHITE);
            }

            DrawRectangleRec(buttonRect, LIGHTGRAY);
            DrawText("Toggle Camera", buttonRect.x + 10, buttonRect.y + 10, 20, BLACK);
            DrawRectangleRec(pauseButton, LIGHTGRAY); // << CHANGE >> Отрисовка кнопки паузы
            DrawText(paused ? "Unpause" : "Pause", pauseButton.x + 10, pauseButton.y + 10, 20, BLACK); // << CHANGE >>

            if (shopMenuOpen) {
                RenderShopSidebar(interFont, screenWidth, screenHeight,
                    &money, &wallHP, maxWallHP, &defenderLevel, maxDefenderLevel, 
                    &towers, &towerCount);
            }
            Vector2 cursorPos = GetMousePosition();
            DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
            //DrawFPS(100, 100);/////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (paused) {
                DrawText("PAUSED", screenWidth/2 - MeasureText("PAUSED", 40)/2, screenHeight/2 - 20, 40, RED);
            }
        EndDrawing();
    }
    UnloadMusicStream(Main_music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
