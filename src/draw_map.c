#include "includs.h"
#define MAP_ROWS 5
#define MAP_COLS 5
// Function to draw a tilemap with 1 as red and 0 as white
void DrawTilemap(int tileMap[MAP_ROWS][MAP_COLS], float cellSize) {
    // Loop through each tile in the map
    for (int x = 0; x < MAP_ROWS; x++) {
        for (int z = 0; z < MAP_COLS; z++) {
            // Calculate position of the tile based on grid size and cell size
            Vector3 position = {
                (x - MAP_ROWS / 2) * cellSize + cellSize / 2 ,
                0.0f,
                (z - MAP_COLS / 2) * cellSize + cellSize / 2
            };

            // Choose the color based on the value of tileMap[x][z]
            Color tileColor = (tileMap[x][z] == 1) ? RED : WHITE;

            // Draw the cube for the current tile
            DrawCube(position, cellSize, 0.01f, cellSize, tileColor);

            // Draw the wireframe in DARKGRAY
            DrawCubeWires(position, cellSize, 0.01f, cellSize, DARKGRAY);
        }
    }
}

