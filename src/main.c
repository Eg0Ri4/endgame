#include "includs.h"

bool GetGridCellFromRay(Ray ray, int *cellX, int *cellZ)
{
    if (ray.direction.y == 0.0f)
        return false;

    float t = -ray.position.y / ray.direction.y;
    if (t < 0.0f)
        return false;

    Vector3 hit = {
        ray.position.x + t * ray.direction.x,
        0.0f,
        ray.position.z + t * ray.direction.z};

    *cellX = (int)(hit.x / CELL_SIZE + GRID_SIZE / 2);
    *cellZ = (int)(hit.z / CELL_SIZE + GRID_SIZE / 2);

    if (*cellX < 0 || *cellX >= GRID_SIZE || *cellZ < 0 || *cellZ >= GRID_SIZE)
        return false;

    return true;
}

int main(void)
{
       MainMenu();
      CloseWindow();
 
   
    const int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Click on Grid Cells!");

    Camera3D camera = {0};
    camera.position = (Vector3){7.0f, 15.0f, 10.0f}; // Высокий угол
    camera.target = (Vector3){10.0f, 0.0f, 0.0f};    // Центр сцены
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Color gridColors[GRID_SIZE][GRID_SIZE] = {0}; // Масив кольорів сітки

    Vector2 cursorPos = {-100.0f, -100.0f};
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        HideCursor();
        cursorPos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Ray ray = GetScreenToWorldRay(cursorPos, camera);
            int cellX, cellZ;

            if (GetGridCellFromRay(ray, &cellX, &cellZ))
            {

                gridColors[cellX][cellZ] = (gridColors[cellX][cellZ].r == 255) ? WHITE : RED;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int z = 0; z < GRID_SIZE; z++)
            {
                Vector3 position = {(x - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, 0.0f,
                                    (z - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2};
                DrawCube(position, CELL_SIZE, 0.01f, CELL_SIZE, gridColors[x][z].r ? gridColors[x][z] : WHITE);
                DrawCubeWires(position, CELL_SIZE, 0.01f, CELL_SIZE, DARKGRAY);
            }
        }

        EndMode3D();
        // DrawText("Click on grid cells to change color!", 20, 20, 20, DARKGRAY);

        // inteface
        draw_info(0, 0, 0, 0);
        DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
