#ifndef MAP_H
#define MAP_H


#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#include "include_sdl2.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define COUNT_BLOCKS_WIDTH 16
#define COUNT_BLOCKS_HEIGHT 12

#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

#define BG_TALES_COUNT 16


typedef struct block {
    SDL_Texture* texture;
    struct block* next;
} block;


void BG_list_render(SDL_Renderer* Renderer, block* head);
void BG_list_create(SDL_Renderer* Renderer, block** head);
void add_block(block** end, block** head, SDL_Texture* texture);
int* openMap(char* str_path);
static void init_bg_tales(SDL_Texture* array_tales[BG_TALES_COUNT], SDL_Renderer* Renderer);
block* block_create(SDL_Texture* texture);


#endif // MAP_H
