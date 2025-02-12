
#include "includs.h"

void walls(void) {

    Color gridColors[GRID_SIZE][GRID_SIZE] = { 0 }; // Массив цветов сетки
    // Параметры для разделения стены на три части
    int wallX1 = 15, wallX2 = 30, wallX3 = 45;
    int wallZ = 33; // Z-координата для всех частей стены

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int z = 0; z < GRID_SIZE; z++) {
            Vector3 position = { (x - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, 0.0f, 
                                 (z - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
            DrawCube(position, CELL_SIZE, 0.01f, CELL_SIZE, gridColors[x][z].r ? gridColors[x][z] : WHITE);
            DrawCubeWires(position, CELL_SIZE, 0.01f, CELL_SIZE, DARKGRAY);
        }
    }

    // Отрисовка первой части стены
    Vector3 wallPosition1 = { (wallX1 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
                              (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
    DrawCube(wallPosition1, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
    DrawCubeWires(wallPosition1, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);

    // Отрисовка второй части стены
    Vector3 wallPosition2 = { (wallX2 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
                              (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
    DrawCube(wallPosition2, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
    DrawCubeWires(wallPosition2, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);

    // Отрисовка третьей части стены
    Vector3 wallPosition3 = { (wallX3 - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
                              (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
    DrawCube(wallPosition3, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
    DrawCubeWires(wallPosition3, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);
}
