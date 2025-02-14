#include "includs.h"

void wawes(float *spawnTimer, float spawnInterval){
    float deltaTime = GetFrameTime();
    // Обновление таймера спавна
    *spawnTimer += deltaTime;
    // Проверка, пришло ли время спавна новой волны
    if (*spawnTimer >= spawnInterval) {
        int spawned = 0;
        while ((npcCount + NPC_count) < MAX_NPC && spawned < NPC_count) {
            SpawnRandomNPC();
            spawned++;
            printf("%d\n",npcCount);
        }
        *spawnTimer = 0.0f;  // Сброс таймера после спавна
    }
    // Обновление всех NPC
    for (int i = 0; i < npcCount; i++) {
        UpdateNPC(&npcs[i], deltaTime);
    }
}
