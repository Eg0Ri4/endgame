#ifndef UTILS_H
#define UTILS_H


#include "include_sdl2.h"


SDL_Texture* getTextureFromPath(char* path, SDL_Renderer* Renderer);
int isInsideRect(int x, int y, SDL_Rect Rect);
void showCursor(SDL_Renderer* Renderer, SDL_Texture* cursor_texture);
void getFps(void);
void waitForFps(size_t fps);
void prError(char* str);


#endif // UTILS_H
