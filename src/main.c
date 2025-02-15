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
    Model bgModel = LoadModel("resources/models/ZAMOK2.glb");

    // Load lighting shader
    Shader shader = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");

    // Assign shader to all materials in the model
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
    
    SetTargetFPS(60);

    // MOB Waves
    float spawnTimer = 20.1f;
    float spawnInterval = 10.0f;


while (!WindowShouldClose()) {
        ToggleShop();
        wawes(&spawnTimer, spawnInterval);
    
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
        // Update all arrows
        for (int i = 0; i < MAX_ARROWS; i++) {
            UpdateArrow(&arrows[i], GetFrameTime());
            CheckArrowCollisionWithNPCs(&arrows[i], npcs, npcCount);
        }
        UpdateLightShader(lights, numActiveLights, shader, camera);  // Update shader with light data
        // Rendering
        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);
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
