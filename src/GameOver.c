#include "includs.h"
const int ScreenWidth = 1280, ScreenHeight = 720;
void GameOverScreen(void)
{
    InitWindow(ScreenWidth, ScreenHeight, "Game Over");

    Texture2D background = LoadTexture("resources/images/back.png");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePoint = GetMousePosition();
        Rectangle retryButton = {ScreenWidth / 2 - 100, 300, 200, 50};
        Color buttonColor = DARKGRAY;
        
        if (CheckCollisionPointRec(mousePoint, retryButton))
        {
            buttonColor = LIGHTGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Масштабування фону
        float scaleX = (float)ScreenWidth / background.width;
        float scaleY = (float)ScreenHeight / background.height;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, scale, WHITE);
        
        DrawText("GAME OVER", ScreenWidth / 2 - 100, 150, 40, RED);
        DrawRectangleRec(retryButton, buttonColor);
        DrawText("quit", retryButton.x + 60, retryButton.y + 15, 20, WHITE);
        
        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
} 
