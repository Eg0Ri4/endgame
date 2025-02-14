#include "includs.h"

int main(void) {
    const int screenWidth = 2560, screenHeight = 1440;
    InitWindow(screenWidth, screenHeight, "Game");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 80.0f, 60.0f, 80.0f }; // High-angle view
    camera.target = (Vector3){ -40.0f, 0.0f, 0.0f }; // Center of the scene
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load the castle model
    Model bgModel = LoadModel("resources/models/3D-G.glb");

    // Load lighting shader
    Shader shader = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");

    // Assign shader to all materials in the model
    for (int i = 0; i < bgModel.materialCount; i++) {
        bgModel.materials[i].shader = shader;
    }

    // Create a light
    Light light = CreateLight((Vector3){ -63.0f, 90.0f, 135.0f }, (Color){ 255, 214, 170, 255}, 0.5f);


    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    LoadNPCModel();
    Tower tower = CreateTower((Vector3){ -5.0f, 8.0f, 5.0f }); // Tower position
    Arrow arrows[MAX_ARROWS] = { 0 };
    int currentArrowIndex = 0;
    
    SetTargetFPS(60);

    // MOB Waves
    float spawnTimer = 20.1f;
    float spawnInterval = 10.0f;

while (!WindowShouldClose()) {
        ToggleShop();
        wawes(&spawnTimer, spawnInterval);
    
        HideCursor();
        Vector2 cursorPos = GetMousePosition();

        // Fire an arrow every few seconds
        static float arrowTimer = 1.0f;
        arrowTimer += GetFrameTime();
        if (arrowTimer >= 0.5f) {  
            arrowTimer = 0.0f;
            LaunchArrow(&tower, &arrows[currentArrowIndex], npcs, npcCount);
            currentArrowIndex = (currentArrowIndex + 1) % MAX_ARROWS;
        }
        // Update all arrows
        for (int i = 0; i < MAX_ARROWS; i++) {
            UpdateArrow(&arrows[i], GetFrameTime());
            CheckArrowCollisionWithNPCs(&arrows[i], npcs, npcCount);
        }

        UpdateLightShader(light, shader, camera);  // Update shader with light data
        // Rendering
        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);
            for (int i = 0; i < npcCount; i++) {
                DrawNPC(&npcs[i]);
            }
            
            BeginShaderMode(shader);
            DrawModel(bgModel, (Vector3){0.0f, 1.0f, -1.0f}, 1.0f, WHITE);
            EndShaderMode();

            // Draw the tower
            DrawCube(tower.position, 2.0f, 5.0f, 2.0f, DARKGRAY);

            // Draw all arrows
            for (int i = 0; i < MAX_ARROWS; i++) {
                DrawArrow(arrows[i]);
            }

            // Draw light sphere
            DrawSphere(light.position, 2.0f, WHITE);

            DrawFPS(20, 20);
        EndMode3D();

        DrawShopUI();
        DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    UnloadModel(bgModel);
    UnloadNPCModel();
    UnloadShader(shader);

    return 0;
}
