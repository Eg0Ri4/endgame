#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int initSDL(SDL_Window **window, SDL_Renderer **renderer);
void cleanupSDL(SDL_Window *window, SDL_Renderer *renderer);

#endif // SCREEN_H
