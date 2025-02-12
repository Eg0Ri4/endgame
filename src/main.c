#include "includs.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
    int b_count = 0;

    InitWindow(screenWidth, screenHeight, "raylib");

    Vector2 cursorPos = { -100.0f, -100.0f };
    int isCursorHidden = 0;
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");

    Vector2 b_pos = {200, 150};  
    Vector2 size = {GRID_SIZE*3, GRID_SIZE*3 };

    Vector2 *points = (Vector2*)malloc(b_count * sizeof(Vector2));

    SetTargetFPS(60);               

    while (!WindowShouldClose())
    {
        if (isCursorHidden == 0){
                HideCursor();
                isCursorHidden = 1;
        }
        cursorPos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            b_pos.x = cursorPos.x - (int)cursorPos.x%GRID_SIZE;
            b_pos.y = cursorPos.y - (int)cursorPos.y%GRID_SIZE;
            
            ++b_count;
            points = realloc(points, b_count * sizeof(Vector2));  
            points[b_count - 1] = b_pos; 
        }

        BeginDrawing();
            ClearBackground(RAYWHITE); 
            for (int x = 0; x < screenWidth; x += GRID_SIZE){
            DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
            }
            for (int y = 0; y < screenHeight; y += GRID_SIZE)
            {
            DrawLine(0, y, screenWidth, y, LIGHTGRAY);
            }
            
            for (int i = 0; i< b_count; ++i){
                DrawRectangleV(points[i], size, BLUE);
                
            }
            DrawRectangleV(b_pos, size, RED);

            DrawTextureEx(Cursor_texture, cursorPos, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }
    CloseWindow();        

    free(points);
    return 0;
}

