#include "raylib.h"
#include "includs.h"
#include "npc.h"
#include "global.h"

Wall wall = {
    .position = {
        (wallX1 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2,  // Позиция стены по X
        WALL_HEIGHT / 2,  // Позиция по Y
        (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2   // Позиция стены по Z
    },
    .width = WALL_WIDTH,
    .height = WALL_HEIGHT,
    .depth = WALL_weight,
    .health = 1000
};
//для теста отрисовка стены при конечной версии очистить
void DrawWalls(void) {
    if (wallDestroyed == 1) { // Если стена не разрушена, рисуем её
        DrawCube(wall.position, wall.width, wall.height, wall.depth, GRAY);
        DrawCubeWires(wall.position, wall.width, wall.height, wall.depth, DARKGRAY);
    }
}

bool CheckCollisionWithWall(Vector3 npcPos, float npcRadius) {
    BoundingBox wallBox = {
        (Vector3){
            (wallX1 - GRID_SIZE / 2) * CELL_SIZE - WALL_WIDTH / 2,
            0,
            (wallZ - GRID_SIZE / 2) * CELL_SIZE - WALL_weight / 2
        },
        (Vector3){
            (wallX1 - GRID_SIZE / 2) * CELL_SIZE + WALL_WIDTH / 2,
            WALL_HEIGHT,
            (wallZ - GRID_SIZE / 2) * CELL_SIZE + WALL_weight / 2
        }
    };

    BoundingBox npcBox = {
        (Vector3){npcPos.x - npcRadius, npcPos.y, npcPos.z - npcRadius},
        (Vector3){npcPos.x + npcRadius, npcPos.y + 1.8f, npcPos.z + npcRadius}
    };

    if (CheckCollisionBoxes(npcBox, wallBox)) {
        return true; // Если столкновение с стеной, возвращаем true
    }
    return false; // Если нет столкновения, возвращаем false
}
