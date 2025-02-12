#include "includs.h"

bool GetGridCellFromRay(Ray ray, int *cellX, int *cellZ) {
    if (ray.direction.y == 0.0f) return false;

    float t = -ray.position.y / ray.direction.y;
    if (t < 0.0f) return false;

    Vector3 hit = {
        ray.position.x + t * ray.direction.x,
        0.0f,
        ray.position.z + t * ray.direction.z
    };

    *cellX = (int)(hit.x / CELL_SIZE + GRID_SIZE / 2);
    *cellZ = (int)(hit.z / CELL_SIZE + GRID_SIZE / 2);

    if (*cellX < 0 || *cellX >= GRID_SIZE || *cellZ < 0 || *cellZ >= GRID_SIZE)
        return false; 

    return true;
}

int main(void) {
    const int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Static Wall on Grid");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ -25.0f, 30.0f, -25.0f }; // Высокий угол
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Центр сцены
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Color gridColors[GRID_SIZE][GRID_SIZE] = { 0 }; // Массив цветов сетки
    
    Vector2 cursorPos = { -100.0f, -100.0f };
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png"); 

    SetTargetFPS(60);

    // Параметры для разделения стены на три части
    int wallX1 = 30;//15, wallX2 = 30, wallX3 = 45;
    int wallZ = 33; // Z-координата для всех частей стены


    while (!WindowShouldClose()) {

        HideCursor();
        cursorPos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Ray ray = GetScreenToWorldRay(cursorPos, camera);
            int cellX, cellZ;

            if (GetGridCellFromRay(ray, &cellX, &cellZ)) {
                gridColors[cellX][cellZ] = (gridColors[cellX][cellZ].r == 255) ? WHITE : RED;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

            // Отображение всех клеток сетки
            for (int x = 0; x < GRID_SIZE; x++) {
                for (int z = 0; z < GRID_SIZE; z++) {
                    Vector3 position = { (x - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, 0.0f, 
                                         (z - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
                    DrawCube(position, CELL_SIZE, 0.01f, CELL_SIZE, gridColors[x][z].r ? gridColors[x][z] : WHITE);
                    DrawCubeWires(position, CELL_SIZE, 0.01f, CELL_SIZE, DARKGRAY);
                }
            }

            // Отрисовка первой части стены
            Vector3 wallPosition1 = { (wallX1 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
                                      (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
            DrawCube(wallPosition1, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
            DrawCubeWires(wallPosition1, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);

            // //Отрисовка второй части стены
            // Vector3 wallPosition2 = { (wallX2 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
            //                           (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
            // DrawCube(wallPosition2, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
            // DrawCubeWires(wallPosition2, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);

            // //Отрисовка третьей части стены
            // Vector3 wallPosition3 = { (wallX3 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
            //                           (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
            // DrawCube(wallPosition3, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
            // DrawCubeWires(wallPosition3, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);

            EndMode3D();
            //DrawText("Click on grid cells to change color!", 20, 20, 20, DARKGRAY);
            draw_info(0,0,0,0);
            DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
