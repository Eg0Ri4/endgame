#include "includs.h"
const int screenWidth = 1920, screenHeight = 1080;
bool MainMenu(void)
{  
    Texture2D Cursor_texture = load_texture("resources/images/cursor.png");
    // Load music
    Music music = LoadMusicStream("resources/music/menu.mp3");  
    
    // Play the music
    PlayMusicStream(music);
    SetMusicVolume(music, 0.2f);

    typedef struct Button
    {
        Rectangle bounds;
        Color color;
        const char *text;
    } Button;

    Button buttons[3] = {
        {{screenWidth / 2 - 100, 530, 200, 50}, (Color){139, 69, 19, 180}, "Play"},       
        {{screenWidth / 2 - 100, 600, 200, 50}, (Color){105, 105, 105, 180}, "Settings"}, 
        {{screenWidth / 2 - 100, 680, 200, 50}, (Color){92, 64, 51, 180}, "Quit"}};   

    Texture2D background = LoadTexture("resources/images/castle.png");
    RenderTexture2D lastFrame = LoadRenderTexture(background.width, background.height);
    
    bool menu = true;
    //bool settings = false;
    
    SetTargetFPS(60);
    while (menu)
    {   
        HideCursor();
        Vector2 mousePoint = GetMousePosition();
        UpdateMusicStream(music);
        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionPointRec(mousePoint, buttons[i].bounds))
            {
                buttons[i].color.a = 220; 
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {   
                    UnloadTexture(background);
                }
            }
            else
            {
                buttons[i].color.a = 180; 
            }
        }
        if (CheckCollisionPointRec(mousePoint, buttons[0].bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) menu = false;
        //if (CheckCollisionPointRec(mousePoint, buttons[1].bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) settings = true;
        if (CheckCollisionPointRec(mousePoint, buttons[2].bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Масштабування фону по екрану
        DrawTexturePro(background, 
            (Rectangle){0, 0, background.width, background.height}, 
            (Rectangle){0, 0, screenWidth, screenHeight}, 
            (Vector2){0, 0}, 0.0f, WHITE);
        if(menu){
        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRounded(buttons[i].bounds, 0.3f, 10, buttons[i].color);

            // Вирівнювання тексту по центру кнопки
            int textWidth = MeasureText(buttons[i].text, 20);
            DrawText(buttons[i].text, buttons[i].bounds.x + (buttons[i].bounds.width - textWidth) / 2,
                     buttons[i].bounds.y + (buttons[i].bounds.height - 20) / 2, 20, WHITE);
        }}

        DrawTextureEx(Cursor_texture, mousePoint, 0.0f, 0.1f, WHITE);
        EndDrawing();
        
    }
    UnloadMusicStream(music);
    UnloadTexture(background);
    UnloadTexture(Cursor_texture);
    UnloadRenderTexture(lastFrame);
    return false;
}
