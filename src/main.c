#include "includs.h"
#include "shop.h"      // Include our shop module (with gold cube functions)
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
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Game");

    // Load font for UI
    Font interFont = LoadFont("resources/fonts/Inter-Regular.ttf");
    SetTextureFilter(interFont.texture, TEXTURE_FILTER_BILINEAR);

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
    cam2.fovy     = 75.0f;
    cam2.projection = CAMERA_PERSPECTIVE;

    // Start with cam1
    Camera3D camera = cam1;
    bool animating = false;
    bool camState = false;
    float t = 0.0f;
    const float transitionDuration = 1.2f;

    // Button to toggle camera (UI)
    Rectangle buttonRect = { 20, 20, 200, 40 };

    // Load castle model
    Model bgModel = LoadModel("resources/models/3D-G.glb");

    // Load lighting shader
    Shader shader = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");
    for (int i = 0; i < bgModel.materialCount; i++) {
        bgModel.materials[i].shader = shader;
    }

    Light light = CreateLight((Vector3){ -63.0f, 90.0f, 135.0f },
                              (Color){ 255, 214, 170, 255}, 0.5f);

    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    // Load NPC model and create tower
    LoadNPCModel();
    Tower tower = CreateTower((Vector3){ -5.0f, 8.0f, 5.0f });

    // Arrow array
    Arrow arrows[MAX_ARROWS] = { 0 };
    int currentArrowIndex = 0;

    SetTargetFPS(300);

    // Parameters for mob waves (dummy logic)
    float spawnTimer = 20.1f;
    float spawnInterval = 10.0f;

    // --- Shop / Menu variables ---
    bool shopMenuOpen = false;
    int money = 1000;
    int wallHP = 440, maxWallHP = 2000;
    int defenderLevel = 0, maxDefenderLevel = 3;

    // --- Gold Cube (Shop Button) variables ---
    Vector3 goldCubePos = { -8.0f, 8.0f, -25.0f };
    float goldCubeSize = 42.0f;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        Vector2 mousePoint = GetMousePosition();

        // --- Shop Toggle Logic via Gold Cube Click ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (shopMenuOpen) {
                // If shop is open, clicking outside the shop sidebar closes it.
                Rectangle shopRect = { (float)(screenWidth - 300), 0, 300, screenHeight };
                if (!CheckCollisionPointRec(mousePoint, shopRect)) {
                    shopMenuOpen = false;
                }
            } else {
                // If shop is closed, check for click on gold cube.
                Ray ray = GetMouseRay(mousePoint, camera);
                if (CheckGoldCubeCollision(ray, goldCubePos, goldCubeSize)) {
                    shopMenuOpen = true;
                }
            }
        }

        // Dummy mob wave logic
        wawes(&spawnTimer, spawnInterval);

        // --- Camera Toggle Logic (via UI button) ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, buttonRect)) {
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

        HideCursor();
        Vector2 cursorPos = GetMousePosition();

        // --- Arrow Launching Logic ---
        static float arrowTimer = 1.0f;
        arrowTimer += deltaTime;
        if (arrowTimer >= 0.5f) {
            arrowTimer = 0.0f;
            LaunchArrow(&tower, &arrows[currentArrowIndex], npcs, npcCount);
            currentArrowIndex = (currentArrowIndex + 1) % MAX_ARROWS;
        }
        for (int i = 0; i < MAX_ARROWS; i++) {
            UpdateArrow(&arrows[i], deltaTime);
            CheckArrowCollisionWithNPCs(&arrows[i], npcs, npcCount);
        }

        UpdateLightShader(light, shader, camera);

        BeginDrawing();
            ClearBackground(BLUE);

            // --- UI: Camera Toggle Button ---
            DrawRectangleRec(buttonRect, LIGHTGRAY);
            DrawText("Toggle Camera", buttonRect.x + 10, buttonRect.y + 10, 20, BLACK);

            // --- 3D Drawing ---
            BeginMode3D(camera);
                // Draw NPCs
                for (int i = 0; i < npcCount; i++) {
                    DrawNPC(&npcs[i]);
                }
                DrawFPS(10, 10);
                BeginShaderMode(shader);
                    DrawModel(bgModel, (Vector3){ 0.0f, 1.0f, -1.0f }, 1.0f, WHITE);
                EndShaderMode();

                // Draw Tower
                DrawCube(tower.position, 2.0f, 5.0f, 2.0f, DARKGRAY);

                // Draw Arrows
                for (int i = 0; i < MAX_ARROWS; i++) {
                    DrawArrow(arrows[i]);
                }

                // Draw Light Sphere
                DrawSphere(light.position, 2.0f, WHITE);

                // --- Draw the Gold Cube (Shop Button) via shop module ---
                DrawGoldCube(goldCubePos, goldCubeSize);
            EndMode3D();

            // --- On-Screen Text ---
            DrawText("Press the button to toggle camera", 20, 70, 20, DARKGRAY);
            DrawText("Click the Gold Cube to open shop", 20, 100, 20, DARKGRAY);

            // --- Render Shop UI if Open ---
            if (shopMenuOpen) {
                RenderShopSidebar(interFont, screenWidth, screenHeight,
                                  &money, &wallHP, maxWallHP, &defenderLevel, maxDefenderLevel);
            }

            DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
            DrawFPS(100, 100);
        EndDrawing();
    }

    // --- Clean Up ---
    UnloadModel(bgModel);
    UnloadNPCModel();
    UnloadShader(shader);
    UnloadFont(interFont);
    CloseWindow();

    return 0;
}
