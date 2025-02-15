#include "includs.h"

void mx_play_music(const char *filePath)
{         

    Music music = LoadMusicStream(filePath);
    PlayMusicStream(music);

    while (!IsKeyPressed(KEY_ESCAPE))  
    {
        UpdateMusicStream(music);  
    }

    UnloadMusicStream(music);          
}
