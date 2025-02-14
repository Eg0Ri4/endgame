#include "npc.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>

NPC npcs[MAX_NPC];
int npcCount = 0;
int wallDestroyed = 1;
Model npcModel;

void InitNPC(NPC *npc, Vector3 spawnPos) {
    npc->position = spawnPos;
    npc->position.y = 1.5f;  // Поднимаем модель выше земли
    npc->state = MOVING;
    npc->disappearTimer = 1000.0f;
    npc->hp = 100;
    npc->damage = 10;
    npc->attackTimer = NPC_ATTACK_INTERVAL;  // Устанавливаем таймер атаки
}

void LoadNPCModel(void) {
    npcModel = LoadModel("resources/models/chevalier.obj");
    if (npcModel.meshCount == 0) {
        printf("Ошибка загрузки модели NPC!\n");
    }
    Texture2D npcTexture = LoadTexture("resources/shaders/chevalier.bmp");
    Shader shader = LoadShader(
        "resources/shaders/lighting.vs",
        "resources/shaders/lighting.fs"
    );
    npcModel.materials[0].shader = shader;

    // Применяем текстуру к материалу модели
    npcModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = npcTexture;
}


void UpdateNPC(NPC *npc, float deltaTime) {
    Vector3 nextPos = npc->position;
    nextPos.z -= 4.0f * deltaTime;

    if (wall.health <= 0) {
        wallDestroyed = 0;  // Если здоровье стены <= 0, она считается разрушенной
    }
    npc->disappearTimer -= deltaTime;
    if (npc->hp <= 0 || npc->disappearTimer <= 0) {
        RemoveNPC(npc);  // Remove NPC from the array
        return;
    }
    if (wallDestroyed == 1 && CheckCollisionWithWall((Vector3){ nextPos.x, nextPos.y, nextPos.z }, 0.5f)) {
        nextPos.z += 4.0f * deltaTime; // Откат назад, если стена цела

        if ((rand() % 100) < 5) {  
            nextPos.z += 100.0f * deltaTime;  // Откидываем еще на 1 фрейм
        }

        npc->attackTimer -= deltaTime;
        if (npc->attackTimer <= 0.0f) {
            wall.health -= npc->damage;
            npc->attackTimer = NPC_ATTACK_INTERVAL;
            printf("NPC ударил стену! Стена получила %d урона, здоровье стены: %d\n", npc->damage, wall.health);
        }
    }
    else {
        npc->state = MOVING; // Если стена разрушена, NPC двигается дальше
    }

    npc->position = nextPos;
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
// спам врагами с уникальными координатами
void SpawnRandomNPC(void) {
    if (npcCount + NPC_count >= MAX_NPC) return;

    float randomX, randomZ;
    bool isValidSpawn = false;

    while (!isValidSpawn) {
        randomX = -40.0f + (rand() % 70);  //-40 70Генерация случайной X координаты
        randomZ = 110.0f + (rand() % 4);  // 5Генерация случайной Z координаты
        
        // Проверка на уникальность комбинации (X, Z)
        isValidSpawn = true; // Сначала предполагаем, что комбинация уникальна
        for (int i = 0; i < npcCount; i++) {
            // Сравнение обеих координат для уникальности
            if (npcs[i].position.x == randomX && npcs[i].position.z == randomZ) {
                isValidSpawn = false; // Если такая комбинация уже есть, меняем флаг
                break; // Выход из цикла, если найдено совпадение
            }
        }
    }

    Vector3 spawnPos = { randomX, 0.0f, randomZ };
    
    InitNPC(&npcs[npcCount], spawnPos);

    npcCount++;
}

// обычный спам врагами не убирать потому что супер вариант который не ломаеться
// void SpawnRandomNPC(void) {
//     if (npcCount >= MAX_NPC) return;

//     int randomX = -40 + (rand() % 70);
//     int randomZ = 105 + (rand() % 21);

//     Vector3 spawnPos = {
//         (float)randomX, 
//         0.0f,           // Опускаем NPC на землю
//         (float)randomZ  
//     };

//     InitNPC(&npcs[npcCount], spawnPos);
//     npcCount++;

//     printf("Spawned NPC at: X=%.2f, Z=%.2f\n", spawnPos.x, spawnPos.z);
// }

void UnloadNPCModel(void) {
    UnloadModel(npcModel);
}

void RemoveNPC(NPC *npc) {
    for (int i = 0; i < npcCount; i++) {
        if (&npcs[i] == npc) {  // Find NPC in the array
            // Shift remaining NPCs down
            for (int j = i; j < npcCount - 1; j++) {
                npcs[j] = npcs[j + 1];
            }
            npcCount--;  // Reduce NPC count
            printf("NPC removed from game!\n");
            return;
        }
    }
}
