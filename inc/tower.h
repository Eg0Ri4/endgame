#ifndef TOWER_H
#define TOWER_H

#include "includs.h"  // Include the full NPC definition here
#define FIRERATE 1.0f
#define MAX_SHOOTERS 22
#define MAX_ARROWS 100 

typedef struct {
    Vector3 position;
    bool isShooting;
    float arrowTimer;
    float frameCounter;
} Tower;

// Arrow Structure
typedef struct {
    Vector3 position;
    Vector3 velocity;
    bool isActive;
    int damage;  // Damage of the arrow
} Arrow;

// Function prototypes
Tower CreateTower(Vector3 position);
void LaunchArrow(Tower* tower, Arrow* arrows, NPC* npcs, int npcCount);
void UpdateArrow(Arrow* arrow, float deltaTime);
void DrawArrow(Arrow arrow);
void CheckArrowCollisionWithNPCs(Arrow* arrow, NPC* npcs, int npcCount);  // Use NPC directly now
void AddTower(Tower **towers, int *towerCount, Vector3 position);
void LoadTowerModel(void);

#endif // TOWER_H
