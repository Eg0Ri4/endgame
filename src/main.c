#include "includs.h"

int main(void) {
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Static Wall on Grid");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 60.0f, 40.0f, 60.0f }; // Высокий угол
    camera.target = (Vector3){ -40.0f, 0.0f, 0.0f }; // Центр сцены
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load the castle model
    Model bgModel = LoadModel("resources/models/3D-G.glb");
    Color gridColors[GRID_SIZE][GRID_SIZE] = { 0 }; // Массив цветов сетки

    Vector2 cursorPos = { -100.0f, -100.0f };
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    LoadNPCModel();
    SetTargetFPS(60);

    //MOBSS WAWES 
    float spawnTimer = 10.1f;  // Timer for NPC spawning
    float spawnInterval = 2.0f;  // Time interval in seconds to spawn NPCs
    
    while (!WindowShouldClose()) {
    ToggleShop();
        //MOBSS FUNc
        wawes(&spawnTimer, spawnInterval);
    
        HideCursor();
        cursorPos = GetMousePosition();
        int cellX, cellZ;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Ray ray = GetScreenToWorldRay(cursorPos, camera);
            if (GetGridCellFromRay(ray, &cellX, &cellZ)) {
                gridColors[cellX][cellZ] = (gridColors[cellX][cellZ].r == 255) ? WHITE : RED;
            }
        }

        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);

            for (int i = 0; i < npcCount; i++) {
                DrawNPC(&npcs[i]);
            }
            DrawModel(bgModel, (Vector3){0.0f, 1.0f, -1.0f}, 1.0f, WHITE);

            DrawFPS(20, 20);
        EndMode3D();

        DrawShopUI();
        // Cursor rendering
        DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }

    CloseWindow();

    UnloadModel(bgModel);
    UnloadNPCModel();
    return 0;
}
