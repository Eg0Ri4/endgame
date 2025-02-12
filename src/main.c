#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#define GRID_SIZE 10

Vector2* delete_element(Vector2* array, int* size, int index) {
    if (*size == 0 || index >= *size) return array; 
    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1]; 
    }
    *size -= 1;
    array = realloc(array, *size * sizeof(Vector2));

    return array;
}

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
    int b_count = 0;

    InitWindow(screenWidth, screenHeight, "raylib");

    Vector2 cursorPos = { -100.0f, -100.0f };
    int isCursorHidden = 0;
    Image image = LoadImage("resources/images/cursor.png");
    Texture2D Cursor_texture = LoadTextureFromImage(image);
    UnloadImage(image); 

    Vector2 b_pos = {200, 150};  
    Vector2 size = {GRID_SIZE*2, GRID_SIZE*2 };

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

