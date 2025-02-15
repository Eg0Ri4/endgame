#pragma once

#include <stdlib.h>
#include <float.h> 
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>
#include "prototypes.h"
#include "shop.h"
#include "global.h"
#include "light.h"
// screen size
#include "npc.h"
#include "tower.h"

#define GRID_SIZE 20
#define CELL_SIZE 1.0f

// wall
#define WALL_COUNT 200
#define WALL_X_poz 30
#define WALL_weight 1
#define WALL_HEIGHT 8.0f  
#define WALL_WIDTH 80.0f // wall WIDTH

#define wallX1 4
#define wallZ 28
#define WALK_SPEED 8.0f
#define SHOOT_SPEED 8.0f

void wawes(float *spawnTimer, float spawnInterval);
//void drawWall(void);
bool CheckCollisionWithWall(Vector3 npcPos, float npcRadius);
void DrawWalls(void);

typedef struct {
    Vector3 position;  // Позиция стены
    float width;       // Ширина
    float height;      // Высота
    float depth;       // Толщина
    int health;        // Здоровье стены
} Wall;

// Теперь можно использовать extern для переменной wall
extern Wall wall;
extern int wallDestroyed;



