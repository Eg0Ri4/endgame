#ifndef STARTSCREEN_H
#define STARTSCREEN_H


#include <stdlib.h>
#include <stdio.h>

#include "include_sdl2.h"
#include "map.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BG_SPRITES 4


typedef struct ButtonMenu {
    SDL_Rect Rect;
    SDL_Texture* cur_texture;
    SDL_Texture* mouseInside;
    SDL_Texture* mouseOutside;
} ButtonMenu;

typedef struct VolumeMenu {
    SDL_Rect Rect;
    SDL_Texture* cur_texture;
    SDL_Texture* mouseInside_volOn;
    SDL_Texture* mouseOutside_volOn;
    SDL_Texture* mouseInside_volOff;
    SDL_Texture* mouseOutside_volOff;
} VolumeMenu;


int menu(SDL_Renderer* Renderer);
void initMenuBgSprites(SDL_Renderer* Renderer, SDL_Texture* array[BG_SPRITES]);
void initButtons(SDL_Renderer* Renderer, TTF_Font* Font, ButtonMenu* startButton, ButtonMenu* exitButton, VolumeMenu* volumeButton);
SDL_Texture* loadTextTexture(char* string, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* renderer);
void renderInfinityText(SDL_Renderer* Renderer, SDL_Texture* Texture, size_t* displace, int width_picture, int count, float speed);


#endif // STARTSCREEN_H
