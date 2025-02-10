#include "map.h"
#include "utils.h"


void BG_list_render(SDL_Renderer* Renderer, block* head){
    int i = 0, j = 0;
    block* currentBlock = head;
    SDL_Rect Rect;
    for (i = 0; i < COUNT_BLOCKS_HEIGHT; i++){
        for (j = 0; j < COUNT_BLOCKS_WIDTH; j++){
            Rect.x = j * BLOCK_WIDTH;
            Rect.y = i * BLOCK_HEIGHT;
            Rect.w = BLOCK_WIDTH;
            Rect.h = BLOCK_HEIGHT;
            SDL_RenderCopy(Renderer, currentBlock->texture, NULL, &Rect);
            currentBlock = currentBlock->next;
        }
    }
}

void BG_list_create(SDL_Renderer* Renderer, block** head){
    int i, j;
    block* end = NULL;
    int *map;

    SDL_Texture* bg_tales[BG_TALES_COUNT];
    init_bg_tales(bg_tales, Renderer);
    map = openMap("BMPimages/Map/map.txt");

    for (i = 0; i < COUNT_BLOCKS_HEIGHT; i++){
        for (j = 0; j < COUNT_BLOCKS_WIDTH; j++){
            add_block(&end, head, bg_tales[*(map + i * COUNT_BLOCKS_WIDTH + j) - 1]);
        }
    }
}

void add_block(block** end, block** head, SDL_Texture* texture){
    block* newblock = block_create(texture);
    block* currentblock = *end;
    if (*end == NULL){
        *head = newblock;
        *end = newblock;
    }
    else{
        currentblock->next = newblock;
        *end = newblock;
    }
}

int* openMap(char* str_path){
    int* buff = malloc(sizeof(int) * COUNT_BLOCKS_HEIGHT * COUNT_BLOCKS_WIDTH);
    FILE* fp = NULL;
    if ((fp = fopen(str_path, "r")) != NULL){
        char c = 0;
        int i = 0;
        int j = 0;
        int q = 0;
        while (feof(fp) == 0){
            c = getc(fp);
            if (c != ' ' && c != '\n'){
                q++;
                if (q == 1) *(buff + i * COUNT_BLOCKS_WIDTH + j) = c - '0';
                else if (q == 2) *(buff + i * COUNT_BLOCKS_WIDTH + j) =
                    10 * (*(buff + i * COUNT_BLOCKS_WIDTH + j)) + c - '0';
            }
            else if (c == ' ') {
                q = 0;
                j++;
            }
            else if (c == '\n'){
                q = 0;
                j = 0;
                i++;
            }
        }
    }
    else fprintf(stderr, "Cant open map! Path: %s.\n", str_path);
    fclose(fp);
    return buff;
}

static void init_bg_tales(SDL_Texture* array_tales[BG_TALES_COUNT], SDL_Renderer* Renderer){
    size_t i;
    char str_path[30];
    for (i = 0; i < BG_TALES_COUNT; i++){
        sprintf(str_path, "BMPimages/Map/%d.png", i + 1);
        array_tales[i] = getTextureFromPath(str_path, Renderer);
    }
}

block* block_create(SDL_Texture* texture){
    block* newblock = malloc(sizeof(block));
    newblock->texture = texture;
    newblock->next = NULL;
    return newblock;
}
