#include "wave.h"
#include "utils.h"


enemy* createEnemy(SDL_Texture* texture){
    enemy* newEnemy = malloc(sizeof(enemy));
    newEnemy->textureEnemy = texture;
    newEnemy->Max_health = 180;
    newEnemy->health = 180;
    newEnemy->isAlive = 1;
    newEnemy->level = 1;
    newEnemy->angle = MOV_RIGHT;
    newEnemy->inCave = 0;
    newEnemy->price = 20;
    newEnemy->next = NULL;
    return newEnemy;
}

int makeNewWaveIfAllIsDead(enemy* head, SDL_Texture* enemy_sparites[ENEMY_COUNT_SPRITES]){
    enemy* cur_enemy = head;
    size_t count = 0;
    while(cur_enemy != NULL){
        if (cur_enemy->isAlive == 1 && cur_enemy->inCave != 1) return 0;
        cur_enemy = cur_enemy->next;
    }
    cur_enemy = head;
    while (cur_enemy != NULL){
        cur_enemy->Max_health *= 2;
        cur_enemy->health = cur_enemy->Max_health;
        cur_enemy->inCave = 0;
        cur_enemy->isAlive = 1;
        cur_enemy->level++;
        cur_enemy->price += 10;
        if (count < COUNT_IN_WAVE / 2){
            cur_enemy->y = 40;
            cur_enemy->x = -320 + BLOCK_WIDTH * 3 / 2 * count;
        }
        else{
            cur_enemy->y = 400;
            cur_enemy->x = -630 + BLOCK_WIDTH * 3 / 2 * count;
        }
        count++;
        cur_enemy->textureEnemy = enemy_sparites[cur_enemy->level - 1];
        cur_enemy = cur_enemy->next;
    }
    return 1;
}

void createListEnemy(enemy** head, SDL_Renderer* Renderer, SDL_Texture* enemy_sprites[ENEMY_COUNT_SPRITES]){
    enemy* current_enemy = NULL;
    size_t count;

    for (count = 0; count < COUNT_IN_WAVE; count++){
        add_enemy(head, enemy_sprites[0]);
    }
    current_enemy = *head;
    for (count = 0; count < COUNT_IN_WAVE; count++){
        if (count < COUNT_IN_WAVE / 2){
            current_enemy->position = POS_UP;
            current_enemy->y = 40;
            current_enemy->x = -320 + BLOCK_WIDTH * 3 / 2 * count;
        }
        else{
            current_enemy->position = POS_DOWN;
            current_enemy->y = 400;
            current_enemy->x = -630 + BLOCK_WIDTH * 3 / 2 * count;
        }
        current_enemy = current_enemy->next;
    }
}

void moveEnemies(enemy* head, point points_up[POINTS_COUNT], point points_down[POINTS_COUNT]){
    size_t count = 0;
    int check = 0;
    enemy* current_enemy = head;
    for (count = 0; count < COUNT_IN_WAVE; count++){
        if (current_enemy->position == POS_UP){
            if (current_enemy->y == points_up[0].y) {
                current_enemy->angle = MOV_RIGHT;
                current_enemy->x++;
            }
            if (current_enemy->x == points_up[1].x) {
                current_enemy->y++;
                current_enemy->angle = MOV_DOWN;
            }
            if (current_enemy->y == points_up[1].y) {
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_up[2].x){
                current_enemy->y++;
                current_enemy->angle = MOV_DOWN;
            }
            if (current_enemy->y == points_up[3].y & current_enemy->x < points_up[6].x){
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_up[4].x){
                current_enemy->y++;
                current_enemy->angle = MOV_DOWN;
            }
            if (current_enemy->y == points_up[5].y){
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_up[6].x){
                current_enemy->y--;
                current_enemy->angle = MOV_UP;
            }
            if (current_enemy->x == points_up[8].x){
                current_enemy->y++;
                current_enemy->angle = MOV_DOWN;
            }
        }
        else{
            if (current_enemy->y == points_down[0].y){
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_down[1].x) {
                current_enemy->y--;
                current_enemy->angle = MOV_UP;
            }
            if (current_enemy->y == points_down[2].y & current_enemy->x < points_down[7].x) {
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_down[3].x){
                current_enemy->y--;
                current_enemy->angle = MOV_UP;
            }
            if (current_enemy->y == points_down[4].y & current_enemy->x < points_down[7].x){
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_up[5].x){
                current_enemy->y--;
                current_enemy->angle = MOV_UP;
            }
            if (current_enemy->y == points_up[5].y){
                current_enemy->x++;
                current_enemy->angle = MOV_RIGHT;
            }
            if (current_enemy->x == points_up[6].x){
                current_enemy->y++;
                current_enemy->angle = MOV_DOWN;
            }
            if (current_enemy->x == points_up[8].x){
                current_enemy->y--;
                current_enemy->angle = MOV_UP;
            }
        }
        current_enemy = current_enemy->next;
    }
}

void showHPbar(SDL_Renderer* Renderer, enemy* head){
    SDL_Rect MaxHpRect;
    SDL_Rect CurHpRect;
    while(head != NULL){
        MaxHpRect.x = head->x;
        MaxHpRect.y = head->y - 10;
        MaxHpRect.w = BLOCK_WIDTH;
        MaxHpRect.h = 5;

        CurHpRect.x = head->x;
        CurHpRect.y = head->y - 10;
        CurHpRect.w = (int) BLOCK_WIDTH * head->health / head->Max_health;
        CurHpRect.h = 5;
        if (head->isAlive == 1 ) {
            SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(Renderer, &MaxHpRect);
            SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(Renderer, &CurHpRect);
        }
        head = head->next;
    }
}

void enemyEnterCave(enemy* head, point array_points[POINTS_COUNT], int* hp){
    while(head != NULL){
        if (head->x >= array_points[10].x & head->isAlive == 1) {
            head->isAlive = 0;
            if (*hp > 0 & head->inCave == 0){
                head->inCave = 1;
                *hp -= 10;
            }
        }
        head = head->next;
    }
}

void renderEnemies(SDL_Renderer* Renderer, enemy* head, int animation){
    size_t i = 0;
    SDL_Rect dstRect;
    SDL_Rect srcRect;
    for (i = 0; i < COUNT_IN_WAVE; i++){
        dstRect.x = head->x;
        dstRect.y = head->y;
        dstRect.w = BLOCK_WIDTH;
        dstRect.h = BLOCK_HEIGHT;

        if (head->angle == MOV_RIGHT){
            srcRect.x = animation * PICT_SIZE;
            srcRect.y = 2 * PICT_SIZE;
        }
        if (head->angle == MOV_DOWN){
            srcRect.x = animation * PICT_SIZE;
            srcRect.y = 0;
        }
        if (head->angle == MOV_UP){
            srcRect.x = animation * PICT_SIZE;
            srcRect.y = 3 * PICT_SIZE;
        }
        srcRect.w = PICT_SIZE;
        srcRect.h = PICT_SIZE;
        if (head->isAlive) SDL_RenderCopy(Renderer, head->textureEnemy, &srcRect, &dstRect);
        head = head->next;
    }
}

void initPointsUp(point array_points[POINTS_COUNT]){
    array_points[0] = createPoint(80, 40);
    array_points[1] = createPoint(80, 80);
    array_points[2] = createPoint(240, 80);
    array_points[3] = createPoint(240, 200);
    array_points[4] = createPoint(280, 200);
    array_points[5] = createPoint(280, 240);
    array_points[6] = createPoint(360, 240);
    array_points[7] = createPoint(360, 80);
    array_points[8] = createPoint(440, 80);
    array_points[9] = createPoint(440, 240);
    array_points[10] = createPoint(480, 240);
}

void initPointsDown(point array_points[POINTS_COUNT]){
    array_points[0] = createPoint(80, 400);
    array_points[1] = createPoint(80, 360);
    array_points[2] = createPoint(160, 360);
    array_points[3] = createPoint(160, 280);
    array_points[4] = createPoint(280, 280);
    array_points[5] = createPoint(280, 240);
    array_points[6] = createPoint(360, 240);
    array_points[7] = createPoint(360, 400);
    array_points[8] = createPoint(440, 400);
    array_points[9] = createPoint(440, 240);
    array_points[10] = createPoint(480, 240);
}

point createPoint(int x, int y){
    point new_point;
    new_point.x = x;
    new_point.y = y;
    return new_point;
}

void add_enemy(enemy** head, SDL_Texture* texture){
    enemy* new_enemy = createEnemy(texture);
    enemy* current_enemy = *head;
    if (current_enemy != NULL){
        while (current_enemy->next != NULL){
            current_enemy = current_enemy->next;
        }
        current_enemy->next = new_enemy;
    }
    else *head = new_enemy;
}

void initEnemiesSprites(SDL_Texture* sprites_array[ENEMY_COUNT_SPRITES], SDL_Renderer* Renderer){
    size_t i;
    char str_path[30];
    for (i = 0; i < ENEMY_COUNT_SPRITES; i++){
        sprintf(str_path, "BMPimages/Wave/%d.png", i + 1);
        sprites_array[i] = getTextureFromPath(str_path, Renderer);
    }
}
