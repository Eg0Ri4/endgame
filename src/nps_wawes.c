#include "includs.h"

void wawes(float *spawnTimer, float *miniWaveTimer, float *waveTimer, float waveInterval, int *waveNumber, int *currentNPCCount) {
    float deltaTime = GetFrameTime();

    *spawnTimer += deltaTime;
    *miniWaveTimer += deltaTime;
    *waveTimer += deltaTime;

    if (*spawnTimer >= 0.0f && *spawnTimer < 5.0f) { 
        int spawned = 0;
        while ((npcCount < MAX_NPC) && (spawned < *currentNPCCount) && spawned <= *currentNPCCount) {
            SpawnRandomNPC();
            spawned++;
        }
        *spawnTimer = 10.0f;  // Ждем вторую мини-волну
    }

    if (*miniWaveTimer >= 5.0f && *miniWaveTimer < 10.0f) { 
        int spawned = 0;
        while ((npcCount < MAX_NPC) && (spawned < *currentNPCCount) && spawned <= *currentNPCCount) {
            SpawnRandomNPC();
            spawned++;
        }
        *miniWaveTimer = 10.0f;  // Блокируем повторный спавн
    }

    // Если 60 секунд прошли, запускаем следующую волну
    if (*waveTimer >= waveInterval) {
        *waveTimer = 0.0f;  // Сброс таймера волны
        *spawnTimer = 0.0f; // Готовность к новой мини-волне
        *miniWaveTimer = 0.0f;
        *waveNumber += 1;   // Увеличение номера волны
        if ((*currentNPCCount * 3 + 1) < MAX_NPC)
            *currentNPCCount += 10; // Увеличение количества NPC в мини-волне
        printf("Новая волна: %d, количество NPC: %d\n", *waveNumber, *currentNPCCount * 2);
    }

    // Обновляем всех NPC
    for (int i = 0; i < npcCount; i++) {
        UpdateNPC(&npcs[i], deltaTime);
    }
}
