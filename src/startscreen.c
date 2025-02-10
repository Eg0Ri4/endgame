#include "startscreen.h"
#include "main.h"
#include "utils.h"


int menu(SDL_Renderer* Renderer){
    SDL_Event event;
    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.bmp", Renderer);

    ButtonMenu* startButton = malloc(sizeof(ButtonMenu));
    ButtonMenu* exitButton = malloc(sizeof(ButtonMenu));
    VolumeMenu* volumeButton = malloc(sizeof(VolumeMenu));

    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);

    Mix_Music* musicMenu = Mix_LoadMUS("MIXmusic/space.flac");

    GameStates state = IN_MENU;
    int x, y;
    int volumeOn = 1;

    SDL_Rect menuRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_Texture* array_menu_bg[BG_SPRITES];
    size_t displace_menu_bg_2 = 0;
    size_t displace_menu_bg_3 = 0;
    size_t displace_menu_bg_4 = 0;

    Mix_PlayMusic(musicMenu, -1);
    initButtons(Renderer, Font, startButton, exitButton, volumeButton);
    initMenuBgSprites(Renderer, array_menu_bg);

    while(state == IN_MENU){
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT){
                state = EXIT;
            }
            if (event.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&x, &y);
                if (isInsideRect(x, y, startButton->Rect)) startButton->cur_texture = startButton->mouseInside;
                else startButton->cur_texture = startButton->mouseOutside;

                if (isInsideRect(x, y, exitButton->Rect)) exitButton->cur_texture = exitButton->mouseInside;
                else exitButton->cur_texture = exitButton->mouseOutside;

                if (isInsideRect(x, y, volumeButton->Rect)){
                    if (volumeOn) volumeButton->cur_texture = volumeButton->mouseInside_volOn;
                    else volumeButton->cur_texture = volumeButton->mouseInside_volOff;
                }
                else{
                    if (volumeOn) volumeButton->cur_texture = volumeButton->mouseOutside_volOn;
                    else volumeButton->cur_texture = volumeButton->mouseOutside_volOff;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&x, &y);
                if (isInsideRect(x, y, startButton->Rect)) state = START;

                if (isInsideRect(x, y, exitButton->Rect)) state = EXIT;

                if (isInsideRect(x, y, volumeButton->Rect)){
                    if (volumeOn){
                        volumeOn = 0;
                        Mix_PauseMusic();
                        volumeButton->cur_texture = volumeButton->mouseInside_volOff;
                    }
                    else{
                        volumeOn = 1;
                        Mix_ResumeMusic();
                        volumeButton->cur_texture = volumeButton->mouseInside_volOn;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(Renderer);

        SDL_RenderCopy(Renderer, array_menu_bg[0], NULL, &menuRect);
        renderInfinityText(Renderer, array_menu_bg[1], &displace_menu_bg_2, 544, 2, 1);
        renderInfinityText(Renderer, array_menu_bg[2], &displace_menu_bg_3, 544, 2, 2);
        renderInfinityText(Renderer, array_menu_bg[3], &displace_menu_bg_4, 544, 2, 3);


        SDL_RenderCopy(Renderer, startButton->cur_texture, NULL, &startButton->Rect);
        SDL_RenderCopy(Renderer, volumeButton->cur_texture, NULL, &volumeButton->Rect);
        SDL_RenderCopy(Renderer, exitButton->cur_texture, NULL, &exitButton->Rect);

        showCursor(Renderer, cursor_texture);
        SDL_RenderPresent(Renderer);
        getFps();
        waitForFps(35);
    }
    return state;
}

void initMenuBgSprites(SDL_Renderer* Renderer, SDL_Texture* array[BG_SPRITES]){
    size_t i;
    char str_path[40];
    for (i = 0; i < BG_SPRITES; i++){
        sprintf(str_path, "BMPimages/Parallax/menu_bg_%d.bmp", i + 1);
        array[i] = getTextureFromPath(str_path, Renderer);
    }
}

void initButtons(SDL_Renderer* Renderer, TTF_Font* Font, ButtonMenu* startButton, ButtonMenu* exitButton, VolumeMenu* volumeButton){
    SDL_Color insideColor = {255, 0, 0};
    SDL_Color outsideColor = {0, 0, 255};

    startButton->Rect.x = 120;
    startButton->Rect.y = 40;
    startButton->Rect.w = 400;
    startButton->Rect.h = 160;
    startButton->mouseInside = loadTextTexture("START", Font, insideColor, Renderer);
    startButton->mouseOutside = loadTextTexture("START", Font, outsideColor, Renderer);
    startButton->cur_texture = startButton->mouseOutside;

    exitButton->Rect.x = 240;
    exitButton->Rect.y = 378;
    exitButton->Rect.w = 160;
    exitButton->Rect.h = 64;
    exitButton->mouseInside = loadTextTexture("EXIT", Font, insideColor, Renderer);
    exitButton->mouseOutside = loadTextTexture("EXIT", Font, outsideColor, Renderer);
    exitButton->cur_texture = exitButton->mouseOutside;

    volumeButton->Rect.x = 580;
    volumeButton->Rect.y = 0;
    volumeButton->Rect.w = 60;
    volumeButton->Rect.h = 60;
    volumeButton->mouseInside_volOn = getTextureFromPath("BMPimages/Icons/volumeOnInside.png", Renderer);
    volumeButton->mouseOutside_volOn = getTextureFromPath("BMPimages/Icons/volumeOnOutside.png", Renderer);
    volumeButton->mouseInside_volOff = getTextureFromPath("BMPimages/Icons/volumeOffInside.png", Renderer);
    volumeButton->mouseOutside_volOff = getTextureFromPath("BMPimages/Icons/volumeOffOutside.png", Renderer);
    volumeButton->cur_texture = volumeButton->mouseOutside_volOn;
}

SDL_Texture* loadTextTexture(char* string, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* renderer){
    SDL_Surface* textSurface = TTF_RenderText_Blended(Font, string, textColor);
    SDL_Texture* texture = NULL;
    if (textSurface == NULL){
        prError("Unable to create texture from rendered text");
        return NULL;
    }
    else{
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == NULL){
            prError("Unable to create texture from rendered text");
            return NULL;
        }
        SDL_FreeSurface(textSurface);
    }
    return texture;
}

void renderInfinityText(SDL_Renderer* Renderer, SDL_Texture* Texture, size_t* displace, int width_picture, int count, float speed){
    SDL_Rect textureRect = {*displace, 0, width_picture, SCREEN_HEIGHT};
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, Texture, &textureRect, &screenRect);
    *displace += speed;
    if (*displace + width_picture >= width_picture * count){
        *displace = 0;
    }
}
