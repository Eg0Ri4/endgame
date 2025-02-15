#pragma once
#include "raylib.h"
#include "includs.h"

typedef struct {
    Model model;
    Vector3 position;
    float disappearTimer;
    int hp;
    int damage;
    int state;
    float attackTimer;
    float frameCounter;
    int currentFrame;
    float attackCurrentFrame;
} NPC;

#define MAX_NPC 200
#define NPC_count 50
#define NPC_ATTACK_INTERVAL 1.5f

extern NPC npcs[MAX_NPC];  // 👈 Declare the array as extern
extern int npcCount;       // 👈 Declare the counter as extern

enum NPCState { IDLE, MOVING, ATTACK, DEAD };

void InitNPC(NPC *npc, Vector3 spawnPos);
void UpdateNPC(NPC *npc, float deltaTime);
void DrawNPC(NPC *npc);
void SpawnRandomNPC(void);
void UnloadNPCModel(void);
void LoadNPCModel(void);
void RemoveNPC(NPC *npc);

