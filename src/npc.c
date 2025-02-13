#include "npc.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>

NPC npcs[MAX_NPC];
int npcCount = NPC_count;
Model npcModel;

void InitNPC(NPC *npc, Vector3 spawnPos) {
    npc->position = spawnPos;
    npc->position.y = 1.5f;  // Поднимаем модель выше земли
    npc->state = MOVING;
    npc->disappearTimer = 90.0f;
    npc->hp = 100;
    npc->damage = 10;
}

void LoadNPCModel(void) {
    npcModel = LoadModel("resources/models/chevalier.obj");
    if (npcModel.meshCount == 0) {
        printf("Ошибка загрузки модели NPC!\n");
    }
    Texture2D npcTexture = LoadTexture("resources/shaders/chevalier.bmp");

    // Применяем текстуру к материалу модели
    npcModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = npcTexture;
}

void UpdateNPC(NPC *npc, float deltaTime) {
    if (npc->state == IDLE) return;

    npc->position.z -= 6.0f * deltaTime;  // Movement based on time
    npc->disappearTimer -= deltaTime;

    if (npc->disappearTimer <= 0) {
        npc->state = IDLE;
    }
}

void DrawNPC(NPC *npc) {
    if (npc->state == MOVING) {
        DrawModelEx(npcModel, 
                    npc->position, 
                    (Vector3){0, 1, 0},  // Ось вращения (Y)
                    180.0f,              // Угол поворота
                    (Vector3){2.0f, 2.0f, 2.0f},  // Масштаб
                    WHITE);
    }
}

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

void UnloadNPCModel(void) {
    UnloadModel(npcModel);
}
