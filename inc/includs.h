#pragma once

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>
#include "prototypes.h"
#include <shop.h>
#include <global.h>
// screen size
#include "npc.h"

#define GRID_SIZE 20
#define CELL_SIZE 1.0f

// wall
#define WALL_COUNT 40
#define WALL_X_poz 30
#define WALL_weight 2
#define WALL_HEIGHT 4.0f  
#define WALL_WIDTH 50.0f

void wawes(float *spawnTimer, float spawnInterval);
