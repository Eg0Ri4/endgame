#ifndef SHOP_H
#define SHOP_H

#include "includs.h"

// Existing RenderShopSidebar declaration
void RenderShopSidebar(Font interFont, int screenWidth, int screenHeight, 
    int* money, int* wallHP, int maxWallHP, 
    int* defenderLevel, int maxDefenderLevel,
    Tower **towers, int *towerCount);


// --- New Function Prototypes ---
// Check if a ray collides with the gold cube.
bool CheckGoldCubeCollision(Ray ray, Vector3 cubePos, float cubeSize);

// Draw the gold cube (shop button) in the 3D world.
void DrawGoldCube(Vector3 cubePos, float cubeSize);

#endif // SHOP_H
