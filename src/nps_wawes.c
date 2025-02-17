#include "includs.h"

void wawes(float *spawnTimer, float *miniWaveTimer, float *waveTimer, float waveInterval, int *waveNumber, int *currentNPCCount) {
    float deltaTime = GetFrameTime();

    *spawnTimer += deltaTime;
    *miniWaveTimer += deltaTime;
    *waveTimer += deltaTime;

    if (*spawnTimer >= 0.0f && *spawnTimer < 5.0f) { 
        int spawned = 0;
        while (((*currentNPCCount * 2 + 1) < MAX_NPC) && (spawned < *currentNPCCount)) {
            SpawnRandomNPC();
            spawned++;
        }
        *spawnTimer = 10.0f;
    }

    if (*miniWaveTimer >= 5.0f && *miniWaveTimer < 10.0f) { 
        int spawned = 0;
        while (((*currentNPCCount * 2 + 1) < MAX_NPC) && (spawned < *currentNPCCount)) {
            SpawnRandomNPC();
            spawned++;
        }
        *miniWaveTimer = 10.0f;
    }

    if (*waveTimer >= waveInterval) {
        *waveTimer = 0.0f;
        *spawnTimer = 0.0f;
        *miniWaveTimer = 0.0f;
        *waveNumber += 1;
        if ((*currentNPCCount * 3 + 1) < MAX_NPC)
            *currentNPCCount += 10;
        printf("Новая волна: %d, количество NPC: %d\n", *waveNumber, *currentNPCCount * 2);
    }

    for (int i = 0; i < npcCount; i++) {
        UpdateNPC(&npcs[i], deltaTime);
    }
}
