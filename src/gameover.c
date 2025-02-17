#include "includs.h"

const int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;

void GameOverScreen(void) {
    Texture2D background = LoadTexture("src/gameover.png");
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");
    // Load music
    Music music = LoadMusicStream("resources/music/menu.mp3");  
    
    // Play the music
    PlayMusicStream(music);
    SetMusicVolume(music, 1.0f);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {   
        Vector2 mousePoint = GetMousePosition();
        Rectangle retryButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 30, 200, 50};
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
        ClearBackground(BLACK);
        
        // Масштабування фону
        float scaleX = (float)SCREEN_WIDTH / background.width;
        float scaleY = (float)SCREEN_HEIGHT / background.height;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;
        DrawTextureEx(background, (Vector2){(SCREEN_WIDTH - background.width * scale) / 2, (SCREEN_HEIGHT - background.height * scale) / 2}, 0.0f, scale, WHITE);
        
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 100, 40, RED);
        DrawRectangleRec(retryButton, buttonColor);
        DrawText("quit", retryButton.x + (retryButton.width - MeasureText("quit", 20)) / 2, retryButton.y + (retryButton.height - 20) / 2, 20, WHITE);
        DrawTextureEx(Cursor_texture, mousePoint, 0.0f, 0.1f, WHITE);
        EndDrawing();
    }
    UnloadTexture(Cursor_texture);
    UnloadMusicStream(music);
    UnloadTexture(background);
}
