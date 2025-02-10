#ifndef GAME_H
#define GAME_H


#include "include_sdl2.h"
#include "startscreen.h"
#include "wave.h"
#include "tower.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define REWIND_FACTOR (18 / 10)


enum states_tewind {
    IN_REWIND,
    NOT_IN_REWIND
};

typedef struct rewind_button {
    SDL_Texture* rewindOn_inside;
    SDL_Texture* rewindOn_outside;
    SDL_Texture* rewindOff_inside;
    SDL_Texture* rewindOff_outside;
    SDL_Rect Rect;
} rewind_button;


int game(SDL_Renderer* Renderer, block* BGhead);
SDL_Texture* getTextureFromInt(int number, char* buff, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* Renderer);
void clickedRewind(rewind_button* button, SDL_Texture** RewTexture, int x, int y, int* isRewind, int* FPS, tower* tow_head);
void mouseInsideRewindButton(rewind_button* button, SDL_Texture** RewTexture, int x, int y, int IsRewind);
void initRewindButton(rewind_button* button, SDL_Renderer* Renderer);
int getGameState(enemy* enemy_head, int HealthPoint);


#endif // GAME_H
