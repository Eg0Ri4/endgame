#ifndef WAVE_H
#define WAVE_H


#include "include_sdl2.h"
#include "map.h"


#define COUNT_IN_WAVE 10
#define PICT_SIZE 48

#define ENEMY_COUNT_SPRITES 7
#define POINTS_COUNT 11


enum WavePosition {
    POS_UP,
    POS_DOWN
};

enum Direction {
    MOV_UP,
    MOV_DOWN,
    MOV_RIGHT
};

typedef struct point {
    int x;
    int y;
} point;

typedef struct enemy {
    SDL_Texture* textureEnemy;
    float Max_health;
    float health;
    int angle;
    int price;
    int isAlive;
    int inCave;
    int level;
    int position;
    int x;
    int y;
    struct enemy* next;
} enemy;


enemy* createEnemy(SDL_Texture* texture);
int makeNewWaveIfAllIsDead(enemy* head, SDL_Texture* enemy_sparites[ENEMY_COUNT_SPRITES]);
void createListEnemy(enemy** head, SDL_Renderer* Renderer, SDL_Texture* enemy_sprites[ENEMY_COUNT_SPRITES]);
void moveEnemies(enemy* head, point points_up[POINTS_COUNT], point points_down[POINTS_COUNT]);
void showHPbar(SDL_Renderer* Renderer, enemy* head);
void enemyEnterCave(enemy* head, point array_points[POINTS_COUNT], int* hp);
void renderEnemies(SDL_Renderer* Renderer, enemy* head, int animation);
void initPointsUp(point array_points[POINTS_COUNT]);
void initPointsDown(point array_points[POINTS_COUNT]);
point createPoint(int x, int y);
void add_enemy(enemy** head, SDL_Texture* texture);
void initEnemiesSprites(SDL_Texture* sprites_array[ENEMY_COUNT_SPRITES], SDL_Renderer* Renderer);


#endif // WAVE_H
