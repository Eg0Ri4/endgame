#include "includs.h"

int TowerAnimCount = 0;
ModelAnimation *TowerAnimations = NULL;
Model  towerModel;
int FrameCount;

// Create a tower at a given position
Tower CreateTower(Vector3 position) {
    Tower tower;
    tower.position = position;
    tower.isShooting = false;
    tower.arrowTimer = (float)rand() / (FIRERATE / ((float)rand()/ 0.5));
    tower.currentFrame= 0;
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

    tower->currentFrame += 60.0f;
    float minDistance = 70.0f;
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
        arrow->damage = 40;
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

    Matrix rotationX = MatrixRotateX(DEG2RAD * 90.0f);  // Change from -90 to 90
    Matrix rotationY = MatrixRotateY(DEG2RAD * 180.0f);
    Matrix rotationZ = MatrixRotateZ(DEG2RAD * 180.0f);
    Matrix transform = MatrixMultiply(rotationZ, MatrixMultiply(rotationY, rotationX));
    towerModel.transform = transform;
    TowerAnimations = LoadModelAnimations("resources/models/mag.glb", &TowerAnimCount);
    FrameCount = TowerAnimations[0].frameCount;
}

void DrawTower(Tower *tower) {
    /*if (tower->isShooting) {
        tower->frameCounter += GetFrameTime() * 10.0f;  // ✅ Increase animation speed
        tower->currentFrame = (int)fmod(tower->frameCounter, FrameCount);
        UpdateModelAnimation(towerModel, TowerAnimations[0], tower->currentFrame);
    }
    tower->currentFrame = (int)fmod(tower->frameCounter, FrameCount);
    UpdateModelAnimation(towerModel, TowerAnimations[0], tower->currentFrame);*/
    DrawModel(towerModel, tower->position, 0.025f, WHITE);
}
