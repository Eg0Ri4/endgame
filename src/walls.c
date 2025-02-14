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
    .health = &wallHP
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

void DrawWallHPBar() {
    int barWidth = 600;
    int barHeight = 30;
    int barX = (GetScreenWidth() - barWidth) / 2;
    int barY = 30;

    float hpPercentage = (float)wallHP / MAX_WALL_HP;
    int hpBarWidth = (int)(barWidth * hpPercentage);

    // Фон полосы (чёрный с прозрачностью)
    DrawRectangle(barX, barY, barWidth, barHeight, Fade(BLACK, 0.5f));

    // Полоса HP
    Color hpColor = (hpPercentage > 0.6f) ? GREEN : (hpPercentage > 0.3f) ? YELLOW : RED;
    DrawRectangle(barX, barY, hpBarWidth, barHeight, hpColor);

    // Скругление углов
    DrawRectangleRoundedLines((Rectangle){barX, barY, barWidth, barHeight}, 0.45f, 10, WHITE);

    // Текст с HP
    DrawText(TextFormat("Wall HP: %d / %d", wallHP, MAX_WALL_HP), barX + 200, barY + 5, 22, WHITE);
}
