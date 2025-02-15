#include "includs.h"
#include <math.h>

// Функция сглаженной интерполяции (ускорение в начале и замедление в конце)
float EaseInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : 1.0f - powf(-2.0f * t + 2.0f, 2) / 2.0f;
}

// Функция линейной интерполяции для векторов
Vector3 LerpVector3(Vector3 start, Vector3 end, float t) {
    Vector3 result;
    result.x = start.x + (end.x - start.x) * t;
    result.y = start.y + (end.y - start.y) * t;
    result.z = start.z + (end.z - start.z) * t;
    return result;
}

int main(void) {
    const int screenWidth = 2560, screenHeight = 1440;
    InitWindow(screenWidth, screenHeight, "Game");

    // Инициализация камер
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
    cam2.fovy     = 75.0f;  // Немного увеличенный FOV для более естественного эффекта
    cam2.projection = CAMERA_PERSPECTIVE;

    // Начинаем с первой камеры
    Camera3D camera = cam1;
    // Переменные для анимации камеры
    bool animating = false;   // Флаг, что анимация запущена
    bool camState = false;    // false: cam1 активна, true: cam2 активна
    float t = 0.0f;           // Прогресс анимации (от 0 до 1)
    const float transitionDuration = 1.2f; // Длительность перехода увеличена для плавности

    // Кнопка на экране
    Rectangle buttonRect = { 20, 20, 200, 40 };

    // Загрузка модели замка
    Model bgModel = LoadModel("resources/models/3D-G.glb");

    // Загрузка шейдера освещения
    Shader shader = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");
    for (int i = 0; i < bgModel.materialCount; i++) {
        bgModel.materials[i].shader = shader;
    }

    // Create a lights
    int numActiveLights = 0;  // Number of lights currently in use
    Light lights[MAX_LIGHTS]; 
    AddLight(lights, &numActiveLights, (Vector3){ -63.0f, 90.0f, 135.0f }, (Color){ 255, 214, 170, 255 }, 0.5f);
    AddLight(lights, &numActiveLights, (Vector3){ -07.0f, 12.0f, -22.0f }, (Color){234,35,0, 255 }, 0.2f);
    AddLight(lights, &numActiveLights, (Vector3){ -04.0f, 08.0f, 23.0f }, (Color){234,35,0, 255 }, 0.3f);

    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    LoadNPCModel();
    Tower *towers = NULL;
    int towerCount = 0;
    //AddTower(&towers, &towerCount, (Vector3){ -5.0f, 8.0f, 5.0f });
    Arrow arrows[MAX_ARROWS] = { 0 };
    int currentArrowIndex = 0;

    SetTargetFPS(300);

    // MOB Waves (dummy)
    float spawnTimer = 20.1f;
    float spawnInterval = 10.0f;

    while (!WindowShouldClose()) {

        ToggleShop();
        wawes(&spawnTimer, spawnInterval);

        float deltaTime = GetFrameTime();
        Vector2 mousePoint = GetMousePosition();

        // При нажатии на кнопку запускаем анимацию переключения камеры
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, buttonRect)){
            animating = true;
            t = 0.0f;
            camState = !camState;  // Переключаем состояние: если cam1, то переходим на cam2, и наоборот
        }
        // Если анимация запущена, обновляем прогресс
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

        HideCursor();
        Vector2 cursorPos = GetMousePosition();

        if (IsKeyDown(KEY_SPACE)){
            AddTower(&towers, &towerCount, (Vector3){towerCount*2-34 + ((towerCount*2-34 >= -15)? 16: 0),  6.5f, 16.0f });
            printf("ther are %i towers", towerCount);
        }
        // Fire an arrow every few seconds
        for (int i = 0; i < towerCount; ++i){
            towers[i].arrowTimer += GetFrameTime();
            printf("fuck this %f\n", towers[i].arrowTimer);
            if (towers[i].arrowTimer >= FIRERATE) {  
                towers[i].arrowTimer = 0.0f;  // Reset timer
                LaunchArrow(&towers[i], &arrows[currentArrowIndex], npcs, npcCount);
                currentArrowIndex = (currentArrowIndex + 1) % MAX_ARROWS;
            }
        }
        // Обновляем все стрелы
        for (int i = 0; i < MAX_ARROWS; i++){
            UpdateArrow(&arrows[i], deltaTime);
            CheckArrowCollisionWithNPCs(&arrows[i], npcs, npcCount);
        }

        UpdateLightShader(lights, numActiveLights, shader, camera); // Update shader with light data
        // Rendering
        BeginDrawing();
        ClearBackground(BLUE);

            // 3D-режим с текущей камерой
            BeginMode3D(camera);
                for (int i = 0; i < npcCount; i++) {
                    DrawNPC(&npcs[i]);
                }
                DrawFPS(10, 10);
                BeginShaderMode(shader);
                    for (int i = 0; i < npcCount; i++) {
                        DrawNPC(&npcs[i]);
                    }
                    DrawModel(bgModel, (Vector3){0.0f, 1.0f, -1.0f}, 1.0f, WHITE);
                EndShaderMode();

            for (int i = 0; i < MAX_ARROWS; i++) {
                DrawArrow(arrows[i]);
            }
            for (int i = 0; i < towerCount; ++i){
                DrawSphere(towers[i].position, 1.0f, RED);
            }
            // Draw all arrows
            // Draw light sphere
            //DrawSphere(lights[0].position, 2.0f, WHITE);

            DrawFPS(20, 20);
        EndMode3D();
            // Отрисовка UI: кнопка и текст
            DrawRectangleRec(buttonRect, LIGHTGRAY);
            DrawText("Toggle Camera", buttonRect.x + 10, buttonRect.y + 10, 20, BLACK);


            DrawText("Press the button to toggle camera", 20, 70, 20, DARKGRAY);
            DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
            DrawFPS(100, 100);
        EndDrawing();
    }

    CloseWindow();
    UnloadModel(bgModel);
    UnloadNPCModel();
    UnloadShader(shader);

    return 0;
}
