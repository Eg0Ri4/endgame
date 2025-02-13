#include "includs.h"

int main(void) {
    const int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Static Wall on Grid");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 100.0f, 60.0f, 100.0f }; // Высокий угол
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Центр сцены
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load the castle model
    Model bgModel = LoadModel("resources/models/3D-G.glb");
    Color gridColors[GRID_SIZE][GRID_SIZE] = { 0 }; // Массив цветов сетки


    Vector2 cursorPos = { -100.0f, -100.0f };
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

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


            DrawModel(bgModel, (Vector3){0.0f, 1.0f, -1.0f}, 1.0f, WHITE);

            DrawFPS(20, 20);
        EndMode3D();

        // Cursor rendering
        DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }

    CloseWindow();
    UnloadModel(bgModel);
    return 0;
}
