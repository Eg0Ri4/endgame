#include "npc.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>

NPC npcs[MAX_NPC];
int npcCount = 0;
Model npcModel;
ModelAnimation *npcAnimations = NULL;
int npcAnimCount = 0;
int npcCurrentFrame = 0;
float npcFrameCounter = 0.0f;

void InitNPC(NPC *npc, Vector3 spawnPos) {
    npc->position = spawnPos;
    npc->position.y = 1.5f;  
    npc->state = MOVING;
    npc->disappearTimer = 90.0f;
    npc->hp = 100;
    npc->damage = 10;
}

void LoadNPCModel(void) {
    npcModel = LoadModel("resources/models/monster.glb");  

    if (npcModel.meshCount == 0) {
        printf("Помилка завантаження моделі NPC!\n");
        return;
    }

    printf("Завантажено модель: Meshes = %d, Materials = %d\n", npcModel.meshCount, npcModel.materialCount);
    
    npcAnimations = LoadModelAnimations("resources/models/monster.glb", &npcAnimCount);
    if (npcAnimations == NULL || npcAnimCount == 0) {
        printf("Помилка завантаження анімації!\n");
    } else {
        printf("Завантажено %d анімацій (використовується тільки перша)\n", npcAnimCount);
    }
}

void UpdateNPC(NPC *npc, float deltaTime) {
    if (npc->state == IDLE) return;

    npc->position.z -= 6.0f * deltaTime;  
    npc->disappearTimer -= deltaTime;

    if (npc->disappearTimer <= 0) {
        npc->state = IDLE;
    }

    if (npc->state == MOVING && npcAnimCount > 0) {
        npcFrameCounter += 1.0f * deltaTime;  // Плавний лічильник кадрів
        float frameIndex = fmod(npcFrameCounter, npcAnimations[2].frameCount);  
        
        UpdateModelAnimation(npcModel, npcAnimations[2], (int)frameIndex);
    }
}

void DrawNPC(NPC *npc) {
    if (npc->state == MOVING) {
        Matrix rotationX = MatrixRotateX(DEG2RAD * -90.0f);  // Повертаємо на 90° по X (ставимо на ноги)
        Matrix rotationY = MatrixRotateY(DEG2RAD * 180.0f); // Повертаємо на 180° по Y (щоб дивився вперед)
        
        Matrix transform = MatrixMultiply(rotationY, rotationX); // Об'єднуємо обертання

        npcModel.transform = transform; // Застосовуємо трансформацію до моделі

        DrawModel(npcModel, npc->position, 0.04f, WHITE); // Малюємо NPC
    }
}
void SpawnRandomNPC(void) {
    if (npcCount >= MAX_NPC) return;

    int randomX = -40 + (rand() % 70);
    int randomZ = 105 + (rand() % 21);

    Vector3 spawnPos = {
        (float)randomX, 
        0.0f,           
        (float)randomZ  
    };

    InitNPC(&npcs[npcCount], spawnPos);
    npcCount++;

    printf("Spawned NPC at: X=%.2f, Z=%.2f\n", spawnPos.x, spawnPos.z);
}

void UnloadNPCModel(void) {
    UnloadModel(npcModel);
    if (npcAnimations) {
        UnloadModelAnimations(npcAnimations, npcAnimCount);
        free(npcAnimations);
        npcAnimations = NULL;
        npcAnimCount = 0;
    }
}
