#include "includs.h"

NPC npcs[MAX_NPC];
int npcCount = 0;
int wallDestroyed = 1;
Model npcModel;
ModelAnimation *npcAnimations = NULL;
int npcAnimCount = 0;
int npcCurrentFrame = 0;
float npcFrameCounter = 0.0f;

void TriggerGameOver(void) {
    GameOverScreen();
    CloseWindow();
}

void InitNPC(NPC *npc, Vector3 spawnPos) {
    npc->model = npcModel;
    npc->position = spawnPos;
    npc->position.y = 1.5f;
    npc->state = MOVING;
    npc->disappearTimer = 45.0f;
    npc->hp = 100;
    npc->damage = 10;
    npc->attackTimer = NPC_ATTACK_INTERVAL;
    npc->frameCounter = 0.0f;
    npc->currentFrame = 0;
    npc->attackCurrentFrame = 0.0f;
}

void LoadNPCModel(void) {
    npcModel = LoadModel("resources/models/monster.glb"); 
    npc_shader = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");

    if (npcModel.meshCount == 0) {
        printf("Помилка завантаження моделі NPC!\n");
        return;
    }

    printf("Завантажено модель: Meshes = %d, Materials = %d\n", npcModel.meshCount, npcModel.materialCount);
    
    npcAnimations = LoadModelAnimations("resources/models/monster.glb", &npcAnimCount);
    if (npcAnimations == NULL || npcAnimCount == 0) {
        printf("Помилка завантаження анімації!\n");
    }
    else {
        printf("Завантажено %d анімацій (використовується тільки перша)\n", npcAnimCount);
    }
}

void UpdateNPC(NPC *npc, float deltaTime) {
    if (wall.health <= 0) {
        wallDestroyed = 0;
    }
    if (npc->hp <= 0 && npc->state != DEAD) {
        npc->state = DEAD;

        npc->frameCounter = 0.0f;
        npc->currentFrame = 0;
    }
    if (npc->state == DEAD) {
        npc->frameCounter += 60.0f * deltaTime;
        int deathFrameCount = npcAnimations[0].frameCount;
        if (npc->currentFrame < deathFrameCount) {
            npc->currentFrame = (int)npc->frameCounter;
        } 
        else {
            npc->currentFrame = deathFrameCount - 1;
            money += 10;
            printf("%d",money);
            RemoveNPC(npc);
            return;
        }
        return;
    }

    npc->disappearTimer -= deltaTime;
    if (npc->disappearTimer <= 0) {
        RemoveNPC(npc);
        return;
    }

    npc->frameCounter += 60.0f * deltaTime;
    npc->position.z -= WALK_SPEED * deltaTime;

    if (npc->position.z <= -5.0f) {
        TriggerGameOver();
        return;
    }

    if (!CheckCollisionWithWall(npc->position, 0.5f)) {
        npc->state = MOVING;
    }
    else if (wallDestroyed == 1 && CheckCollisionWithWall(npc->position, 0.5f)) {
        npc->state = ATTACK;
        npc->attackCurrentFrame += 60.0f * deltaTime;
        
        npc->position.z += WALK_SPEED * deltaTime;

        npc->attackTimer -= deltaTime;
        if (npc->attackTimer <= 0.0f) {
            wall.health -= npc->damage;
            npc->attackTimer = NPC_ATTACK_INTERVAL;
            npc->attackCurrentFrame = 0.0f;
            printf("NPC ударил стену! Стена получила %d урона, здоровье стены: %d\n", npc->damage, wall.health);
        }
    }
    else {
        npc->state = MOVING;
    }
}

void DrawNPC(NPC *npc) {
    if (npc->state == DEAD) {
        int deathFrameCount = npcAnimations[0].frameCount;
        int frameToDraw = (npc->currentFrame < deathFrameCount) ? npc->currentFrame : deathFrameCount - 1;
        UpdateModelAnimation(npcModel, npcAnimations[0], frameToDraw);
    } else if (npc->state == ATTACK) {
        UpdateModelAnimation(npcModel, npcAnimations[1], (int)fmod(npc->attackCurrentFrame, npcAnimations[1].frameCount));
    } else { 
        UpdateModelAnimation(npcModel, npcAnimations[2], (int)fmod(npc->frameCounter, npcAnimations[2].frameCount));
    }

    Matrix rotationX = MatrixRotateX(DEG2RAD * -90.0f);
    Matrix rotationY = MatrixRotateY(DEG2RAD * 180.0f);
    Matrix transform = MatrixMultiply(rotationY, rotationX);
    npcModel.transform = transform;
    
    DrawModel(npcModel, npc->position, 0.03f, WHITE);
}

void SpawnRandomNPC(void) {
    if (npcCount + NPC_count >= MAX_NPC) return;

    float randomX, randomZ;
    bool isValidSpawn = false;

    while (!isValidSpawn) {
        randomX = -36.0f + (rand() % 63);
        randomZ = 160.0f + (rand() % 12);
        
        isValidSpawn = true;
        for (int i = 0; i < npcCount; i++) {
            if (npcs[i].position.x == randomX && npcs[i].position.z == randomZ) {
                isValidSpawn = false;
                break;
            }
        }
    }
    Vector3 spawnPos = { randomX, 0.0f, randomZ };
    InitNPC(&npcs[npcCount], spawnPos);
    npcCount++;
}

/* //обычный спам врагами не убирать
void SpawnRandomNPC(void) {
    if (npcCount >= MAX_NPC) return;

    int randomX = -40 + (rand() % 70);
    int randomZ = 105 + (rand() % 21);

    Vector3 spawnPos = {
        (float)randomX, 
        0.0f,           // Опускаем NPC на землю
        (float)randomZ  
    };

    InitNPC(&npcs[npcCount], spawnPos);
    npcCount++;

    printf("Spawned NPC at: X=%.2f, Z=%.2f\n", spawnPos.x, spawnPos.z);
}
*/

void UnloadNPCModel(void) {
    UnloadModel(npcModel);
}

void RemoveNPC(NPC *npc) {
    for (int i = 0; i < npcCount; i++) {
        if (&npcs[i] == npc) {

            for (int j = i; j < npcCount - 1; j++) {
                npcs[j] = npcs[j + 1];
            }
            npcCount--;
            printf("NPC removed from game!\n");
            return;
        }
    }
}
