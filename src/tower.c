#include "includs.h"
#include <float.h>  // For FLT_MAX
#include <stdlib.h>
#include <stdio.h>

Tower CreateTower(Vector3 position) {
    Tower tower;
    tower.position = position;
    tower.isShooting = false;
    return tower;
}

void LaunchArrow(Tower* tower, Arrow* arrow, NPC* npcs, int npcCount) {
    if (!arrow->isActive) {
        float minDistance = FLT_MAX;
        NPC* nearestNPC = NULL;

        for (int i = 0; i < npcCount; i++) {
            if (npcs[i].state != DEAD) {
                float distance = Vector3Distance(tower->position, npcs[i].position);
                if (distance < minDistance && distance < 70.0f) {
                    minDistance = distance;
                    nearestNPC = &npcs[i];
                }
            }
        }

        if (nearestNPC != NULL) {
            arrow->position = tower->position;
            Vector3 direction = Vector3Normalize(Vector3Subtract(nearestNPC->position, tower->position));

            arrow->velocity = Vector3Scale(direction, 150.0f);
            arrow->damage = 100;
            arrow->isActive = true;
        }
    }
}


void UpdateArrow(Arrow* arrow, float deltaTime) {
    if (arrow->isActive) {
        arrow->position = Vector3Add(arrow->position, Vector3Scale(arrow->velocity, deltaTime));

    }
}

void CheckArrowCollisionWithNPCs(Arrow* arrow, NPC* npcs, int npcCount) {
    if (!arrow->isActive) return;

    for (int i = 0; i < npcCount; i++) {
        if (npcs[i].state != DEAD) {
            float distance = Vector3Distance(arrow->position, npcs[i].position);
            if (distance < 2.5f) {  // если расстояние меньше порога столкновения
                npcs[i].hp -= arrow->damage;  // наносим урон
                printf("NPC hit! HP: %d\n", npcs[i].hp);
                arrow->isActive = false;  // стрела исчезает после попадания
                break;  // прекращаем проверку после первого попадания
            }
        }
    }
}

// Draw the arrow
void DrawArrow(Arrow arrow) {
    if (arrow.isActive) {
        DrawSphere(arrow.position, 0.5f, YELLOW);
    }
}
