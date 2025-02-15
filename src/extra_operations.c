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

#include "raylib.h"

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
        {{SCREEN_WIDTH / 2 - 100, 230, 200, 50}, (Color){139, 69, 19, 180}, "Play"},       
        {{SCREEN_WIDTH / 2 - 100, 300, 200, 50}, (Color){105, 105, 105, 180}, "Settings"}, 
        {{SCREEN_WIDTH / 2 - 100, 380, 200, 50}, (Color){92, 64, 51, 180}, "Credits"}};   

    Texture2D background = LoadTexture("resources/images/castle.png");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePoint = GetMousePosition();

        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionPointRec(mousePoint, buttons[i].bounds))
            {
                buttons[i].color.a = 220; 
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    WindowShouldClose();
                    UnloadTexture(background);
                    return;
                }
            }
            else
            {
                buttons[i].color.a = 180; 
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Масштабування фону по екрану
        DrawTexturePro(background, 
            (Rectangle){0, 0, background.width, background.height}, 
            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, 
            (Vector2){0, 0}, 0.0f, WHITE);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRounded(buttons[i].bounds, 0.3f, 10, buttons[i].color);

            // Вирівнювання тексту по центру кнопки
            int textWidth = MeasureText(buttons[i].text, 20);
            DrawText(buttons[i].text, buttons[i].bounds.x + (buttons[i].bounds.width - textWidth) / 2,
                     buttons[i].bounds.y + (buttons[i].bounds.height - 20) / 2, 20, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(background);
    
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
