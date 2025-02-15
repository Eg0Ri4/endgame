#include "includs.h"
const int screenWidth = 1280, screenHeight = 720;
void MainMenu(void)
{  
    InitWindow(screenWidth, screenHeight, "Main Menu");
    InitAudioDevice();

    // Load music
    Music music = LoadMusicStream("resources/music/menu.mp3");  
    
    // Play the music
    PlayMusicStream(music);
    SetMusicVolume(music, 1.0f);

    typedef struct Button
    {
        Rectangle bounds;
        Color color;
        const char *text;
    } Button;

    Button buttons[3] = {
        {{screenWidth / 2 - 100, 330, 200, 50}, (Color){139, 69, 19, 180}, "Play"},       
        /*{{screenWidth / 2 - 100, 400, 200, 50}, (Color){105, 105, 105, 180}, "Settings"}, 
        {{screenWidth / 2 - 100, 480, 200, 50}, (Color){92, 64, 51, 180}, "Credits"}*/};   

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
            (Rectangle){0, 0, screenWidth, screenHeight}, 
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
    UnloadMusicStream(music);
    CloseAudioDevice();
    UnloadTexture(background);
    
}
