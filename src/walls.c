#include "includs.h"

void drawWall(int wallX){
    const int wallZ = 33;
    Vector3 wallPosition1 = { (wallX - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2, WALL_HEIGHT / 2, 
        (wallZ - GRID_SIZE / 2) * CELL_SIZE + CELL_SIZE / 2 };
    DrawCube(wallPosition1, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, GRAY);  // Треть ширины
    DrawCubeWires(wallPosition1, WALL_WIDTH * CELL_SIZE / 3, WALL_HEIGHT, CELL_SIZE, DARKGRAY);
}
