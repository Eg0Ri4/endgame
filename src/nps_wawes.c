#include "includs.h"

void wawes(float *spawnTimer, float spawnInterval){
    float deltaTime = GetFrameTime();
    // Обновление таймера спавна
    *spawnTimer += deltaTime;
    // Проверка, пришло ли время спавна новой волны
    if (*spawnTimer >= spawnInterval) {
        int spawned = 0;
        while (spawned < NPC_count && npcCount < MAX_NPC) {
            SpawnRandomNPC();
            spawned++;
        }
        *spawnTimer = 0.0f;  // Сброс таймера после спавна
    }
    // Обновление всех NPC
    int activeNPCs = 0;
    for (int i = 0; i < npcCount; i++) {
        UpdateNPC(&npcs[i], deltaTime);
        if (npcs[i].state != IDLE) {
            activeNPCs++;  // Подсчет живых NPC
        }
    }
    // Если все NPC исчезли, сбрасываем счетчик
    if (activeNPCs == 0) {
        npcCount = 0;
    }
}
