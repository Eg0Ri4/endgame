#include "utils.h"


SDL_Texture* getTextureFromPath(char* path, SDL_Renderer* Renderer){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    if ((loadedSurface = IMG_Load(path)) == NULL)
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    else {
        if ((newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface)) == NULL){
            fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

int isInsideRect(int x, int y, SDL_Rect Rect){
    if (Rect.x <= x & x <= Rect.x + Rect.w & Rect.y <= y & y <= Rect.y + Rect.h) return 1;
    else return 0;
}

void showCursor(SDL_Renderer* Renderer, SDL_Texture* cursor_texture){
    int x, y;
    SDL_Rect cursorRect;
    SDL_GetMouseState(&x, &y);
    cursorRect.x = x;
    cursorRect.y = y;
    cursorRect.w = 25;
    cursorRect.h = 25;
    SDL_RenderCopy(Renderer, cursor_texture, NULL, &cursorRect);
}

void getFps(void){
    static size_t frameWindow = 0;
    static size_t currentTime1 = 0;
    static size_t currentTime2 = 0;
    static float fps = 0;
    frameWindow++;

    if (frameWindow % 100 == 0){
        currentTime2 = SDL_GetTicks();
        fps = (float) frameWindow * 1000 / (currentTime2 - currentTime1);
        printf("FPS: %0.2f\n", fps);
        currentTime1 = currentTime2;
        currentTime2 = 0;
        frameWindow = 0;
    }
}

void waitForFps(size_t fps){
    static float timer1 = 0;
    static float delta = 0;
    static float time = 0;
    time = (float) 1000 / fps;
    delta = SDL_GetTicks() - timer1;
    if (delta < time){
        SDL_Delay(time - delta);
    }
    timer1 = SDL_GetTicks();
}

void prError(char* str){
    fprintf(stderr, "%s! %s\n", str, SDL_GetError());
}
