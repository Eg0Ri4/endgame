#include "includs.h"

int TowerAnimCount = 0;
ModelAnimation *TowerAnimations = NULL;
Model  towerModel;
// Create a tower at a given position
Tower CreateTower(Vector3 position) {
    Tower tower;
    tower.position = position;
    tower.isShooting = false;
    tower.arrowTimer = (float)rand() / (FIRERATE / ((float)rand()/ 0.5));
    tower.frameCounter = 0.0f;
    return tower;
}

// Function to launch the arrow towards the nearest NPC
void LaunchArrow(Tower* tower, Arrow* arrows, NPC* npcs, int npcCount) {
    Arrow* arrow = NULL;

    // Find an inactive arrow to reuse
    for (int i = 0; i < MAX_ARROWS; i++) {
        if (!arrows[i].isActive) {
            arrow = &arrows[i];
            break;
        }
    }

    // No available arrows, return
    if (arrow == NULL) return;


    float minDistance = 50.0f;
    NPC* nearestNPC = NULL;

        for (int i = 0; i < npcCount; i++) {
            if (npcs[i].state != DEAD) {
                float distance = Vector3Distance(tower->position, npcs[i].position);
                if (distance < minDistance && distance < 70.0f) {
                    minDistance = distance;
                    nearestNPC = &npcs[i];
                }
            }
        }

    // Launch arrow towards the nearest NPC
    if (nearestNPC != NULL) {
        arrow->position = tower->position;
        Vector3 direction = Vector3Normalize(Vector3Subtract(nearestNPC->position, tower->position));
        arrow->velocity = Vector3Scale(direction, 150.0f);  // Adjust speed
        arrow->damage = 20;
        arrow->isActive = true;
    }
}


void UpdateArrow(Arrow* arrow, float deltaTime) {
    if (arrow->isActive) {
        arrow->position = Vector3Add(arrow->position, Vector3Scale(arrow->velocity, deltaTime));

    }
}

void CheckArrowCollisionWithNPCs(Arrow* arrow, NPC* npcs, int npcCount) {
    if (!arrow->isActive) return;

    for (int i = 0; i < npcCount; i++) {
        if (npcs[i].state != DEAD) {
            float distance = Vector3Distance(arrow->position, npcs[i].position);
            if (distance < 2.5f) {  // Collision detected
                npcs[i].hp -= arrow->damage;  // Apply damage
                printf("NPC hit! HP: %d\n", npcs[i].hp);  
                arrow->isActive = false;  // Arrow disappears on hit
                break;  // Stop checking other NPCs
            }else if(arrow->position.y < 0){
                arrow->isActive = false;
            }
        }
    }
}

// Draw the arrow
void DrawArrow(Arrow arrow) {
    if (arrow.isActive) {
        DrawSphere(arrow.position, 0.5f, YELLOW);
    }
}

void AddTower(Tower **towers, int *towerCount, Vector3 position) {
    if(*towerCount+1 >= MAX_SHOOTERS ) return;

    (*towerCount)++;
    Tower *temp = (Tower *)realloc(*towers, (*towerCount) * sizeof(Tower));
    if (temp == NULL) {
        printf("ERROR: Memory allocation failed! Exiting...\n");
        free(*towers);
        exit(1);
    }
    *towers = temp;
    (*towers)[(*towerCount) - 1] = CreateTower(position);
}

void LoadTowerModel(void) {
    towerModel = LoadModel("resources/models/mag.glb");  

    if (towerModel.meshCount == 0) {
        printf("Помилка завантаження моделі NPC!\n");
        return;
    }
    TowerAnimations = LoadModelAnimations("resources/models/mag.glb", &TowerAnimCount);
}
