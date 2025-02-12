#include "includs.h"

#include <stdlib.h>

Rectangle walls[WALL_COUNT];  // Стена

void DrawGridLines(int screenWidth, int screenHeight) {
    for (int x = 0; x < screenWidth; x += GRID_SIZE)
        DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
    
    for (int y = 0; y < screenHeight; y += GRID_SIZE)
        DrawLine(0, y, screenWidth, y, LIGHTGRAY);
}

// Проверка, является ли клетка стеной
int is_wall(int x, int y) {
    for (int i = 0; i < WALL_COUNT; i++) {
        if (walls[i].x == x && walls[i].y == y)
            return 1;  // Это стена
    }
    return 0;  // Это проход
}

void InitWalls(int screenWidth) {
    int startX = screenWidth - GRID_SIZE * WALL_X_poz;  // Начало стены справа
    int startY = 0;  // Высота стены

    for (int i = 0; i < WALL_COUNT; i++) {
        walls[i].x = startX;
        walls[i].y = startY + i * GRID_SIZE;
        walls[i].width = GRID_SIZE * 2;
        walls[i].height = GRID_SIZE * 300;
    }
}

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib - Walls");

    InitWalls(screenWidth);  // Создаем стену

    Vector2 cursorPos = { -100.0f, -100.0f };
    int isCursorHidden = 0;
    Texture2D Cursor_texture = LoadTexture("resources/images/cursor.png");

    int blockCount = 0;
    Rectangle *blocks = NULL;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!isCursorHidden) {
            HideCursor();
            isCursorHidden = 1;
        }

        cursorPos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int gridX = (int)cursorPos.x - ((int)cursorPos.x % GRID_SIZE);
            int gridY = (int)cursorPos.y - ((int)cursorPos.y % GRID_SIZE);

            // Проверяем, можно ли разместить блок (не стена)
            if (!is_wall(gridX, gridY)) {
                blockCount++;
                blocks = realloc(blocks, blockCount * sizeof(Rectangle));
                blocks[blockCount - 1] = (Rectangle){ gridX, gridY, GRID_SIZE, GRID_SIZE };
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawGridLines(screenWidth, screenHeight);

            // Рисуем стены (они непроходимые)
            for (int i = 0; i < WALL_COUNT; i++)
                DrawRectangleRec(walls[i], DARKGRAY);

            // Рисуем размещенные блоки (проходимые)
            for (int i = 0; i < blockCount; i++)
                DrawRectangleRec(blocks[i], BLUE);

            // Отображаем красный блок на курсоре
            int gridX = (int)cursorPos.x - ((int)cursorPos.x % GRID_SIZE);
            int gridY = (int)cursorPos.y - ((int)cursorPos.y % GRID_SIZE);
            
            if (!is_wall(gridX, gridY))
                DrawRectangle(gridX, gridY, GRID_SIZE, GRID_SIZE, RED);

            DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }

    UnloadTexture(Cursor_texture);
    free(blocks);
    CloseWindow();

    return 0;
}
