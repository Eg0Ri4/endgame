#pragma once
#include "raylib.h"
#include "includs.h"

typedef struct {
    Vector3 position;
    float disappearTimer;
    int hp;
    int damage;
    int state;
} NPC;

#define MAX_NPC 101
#define NPC_count 20

extern NPC npcs[MAX_NPC];  // 👈 Declare the array as extern
extern int npcCount;       // 👈 Declare the counter as extern

enum NPCState { IDLE, MOVING };

void InitNPC(NPC *npc, Vector3 spawnPos);
void UpdateNPC(NPC *npc, float deltaTime);
void DrawNPC(NPC *npc);
void SpawnRandomNPC(void);
void UnloadNPCModel(void);
void LoadNPCModel(void);
