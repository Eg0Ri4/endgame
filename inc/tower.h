#ifndef TOWER_H
#define TOWER_H


#include <math.h>

#include "include_sdl2.h"
#include "map.h"
#include "wave.h"


#define COUNT_TOWER 5
#define COUNT_SPRITES_TOWER 8
#define PI 3.14159265


typedef struct tower {
    SDL_Texture* texture;
    float damage;
    int level;
    int cost;
    int x;
    int y;
    int angle;
    int radius;
    struct tower* next;
} tower;


void initTowerTextures(SDL_Texture* enemy_sprites[COUNT_SPRITES_TOWER], SDL_Renderer* Renderer);
tower* clickedOnTowerPosition(tower* head, int x, int y);
void renderTowersAndShoot(tower* tow_head, enemy* enemy_head, SDL_Renderer* Renderer, int* Gold);
void renderShootingInEnemy(SDL_Renderer* Renderer, enemy* cur_enemy, tower* cur_tower, int* Gold);
void clickedUpgradeMenu(tower* cur_tower, SDL_Texture* tow_textures[COUNT_SPRITES_TOWER], int x, int y, int* gold);
void upgradeTower(tower* cur_tower, SDL_Texture* tow_textures[COUNT_SPRITES_TOWER], int* gold);
void destroyTower(tower* cur_tower, int* gold);
void showTowerUpgradeMenu(tower* cur_tower, SDL_Renderer* Renderer, SDL_Texture* tow_textures[COUNT_SPRITES_TOWER], int gold);
void createListTower(tower** head);
void addTower(tower** head);
void makeStartStatesForTower(tower* cur_tower);
tower* createTower(void);
void initTowerTextures(SDL_Texture* enemy_sprites[COUNT_SPRITES_TOWER], SDL_Renderer* Renderer);


#endif // TOWER_H
