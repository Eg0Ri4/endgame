#include "includs.h"

Vector2 *delete_element(Vector2 *array, int *size, int index)
{
    if (*size == 0 || index >= *size)
        return array;
    for (int i = index; i < *size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    *size -= 1;
    array = realloc(array, *size * sizeof(Vector2));

    return array;
}

Texture2D load_texture(char *file_path)
{
    Image image = LoadImage(file_path);
    Texture2D results = LoadTextureFromImage(image);
    UnloadImage(image);
    return results;
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

void MainMenu(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main Menu");

    typedef struct Button
    {
        Rectangle bounds;
        Color color;
        const char *text;
    } Button;

    Button buttons[3] = {
        {{SCREEN_WIDTH / 2 - 100, 150, 200, 50}, DARKBLUE, "Play"},
        {{SCREEN_WIDTH / 2 - 100, 220, 200, 50}, DARKGRAY, "Settings"},
        {{SCREEN_WIDTH / 2 - 100, 290, 200, 50}, DARKBROWN, "Credits"}};
    Texture2D background = LoadTexture("src/background.png");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePoint = GetMousePosition();

        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionPointRec(mousePoint, buttons[i].bounds))
            {
                buttons[i].color = LIGHTGRAY;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    WindowShouldClose();

                    UnloadTexture(background);
                    return;
                }
            }
            else
            {
                buttons[i].color = (i == 0) ? DARKBLUE : (i == 1) ? DARKGRAY
                                                                  : DARKBROWN;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Масштабування по ширині екрану
        float scaleX = (float)SCREEN_WIDTH / background.width;
        float scaleY = (float)SCREEN_HEIGHT / background.height;

        // Вибираємо менший масштаб, щоб зберегти пропорції
        float scale = (scaleX < scaleY) ? scaleX : scaleY;

        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, scale, (Color){255, 255, 255, 255});
        DrawText("CASTLE CLASH", SCREEN_WIDTH / 2 - 120, 100, 30, BLACK);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(buttons[i].bounds, buttons[i].color);
            DrawText(buttons[i].text, buttons[i].bounds.x + 60, buttons[i].bounds.y + 15, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}


void GameOverScreen(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Over");

    Texture2D background = LoadTexture("src/gameover.png");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePoint = GetMousePosition();
        Rectangle retryButton = {SCREEN_WIDTH / 2 - 100, 300, 200, 50};
        Color buttonColor = DARKGRAY;
        
        if (CheckCollisionPointRec(mousePoint, retryButton))
        {
            buttonColor = LIGHTGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Додайте логіку для перезапуску гри
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Масштабування фону
        float scaleX = (float)SCREEN_WIDTH / background.width;
        float scaleY = (float)SCREEN_HEIGHT / background.height;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, scale, WHITE);
        
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, 150, 40, RED);
        DrawRectangleRec(retryButton, buttonColor);
        DrawText("Retry", retryButton.x + 60, retryButton.y + 15, 20, WHITE);
        
        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
}
