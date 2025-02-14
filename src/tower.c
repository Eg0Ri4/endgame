#include "includs.h"
#include <float.h>  // For FLT_MAX
#include <stdlib.h>
#include <stdio.h>
// Create a tower at a given position
Tower CreateTower(Vector3 position) {
    Tower tower;
    tower.position = position;
    tower.isShooting = false;
    return tower;
}

// Function to launch the arrow towards the nearest NPC
// Function to launch the arrow towards the nearest NPC
void LaunchArrow(Tower* tower, Arrow* arrow, NPC* npcs, int npcCount) {
    if (!arrow->isActive) {
        float minDistance = FLT_MAX;
        NPC* nearestNPC = NULL;

        // Find the nearest NPC within range
        for (int i = 0; i < npcCount; i++) {
            if (npcs[i].state == MOVING) {
                float distance = Vector3Distance(tower->position, npcs[i].position);
                if (distance < minDistance && distance < 70.0f) {  // Check if within range (e.g., 30 units)
                    minDistance = distance;
                    nearestNPC = &npcs[i];
                }
            }
        }

        // Launch arrow towards the nearest NPC
        if (nearestNPC != NULL) {
            arrow->position = tower->position;
            Vector3 direction = Vector3Normalize(Vector3Subtract(nearestNPC->position, tower->position));
            arrow->velocity = Vector3Scale(direction, 50.0f);  // Adjust speed here
            arrow->damage = 100;  // Arrow damage can be adjusted
            arrow->isActive = true;
            arrow->velocity = Vector3Scale(direction, 150.0f);
        }
    }
}


// Update the arrow's position
void UpdateArrow(Arrow* arrow, float deltaTime) {
    if (arrow->isActive) {
        // Move arrow
        arrow->position = Vector3Add(arrow->position, Vector3Scale(arrow->velocity, deltaTime));

        // ❌ Remove this check: arrows should disappear only on hit
        // if (arrow->position.x > 20.0f || arrow->position.z > 20.0f ||
        //     arrow->position.x < -20.0f || arrow->position.z < -20.0f) {
        //     arrow->isActive = false;
        // }
    }
}

// Check collision between arrow and NPC
// Check collision between arrow and NPC
void CheckArrowCollisionWithNPCs(Arrow* arrow, NPC* npcs, int npcCount) {
    if (!arrow->isActive) return;

    for (int i = 0; i < npcCount; i++) {
        if (npcs[i].state == MOVING) {  
            float distance = Vector3Distance(arrow->position, npcs[i].position);
            if (distance < 2.5f) {  // Collision detected
                npcs[i].hp -= arrow->damage;  // Apply damage
                printf("NPC hit! HP: %d\n", npcs[i].hp);  
                arrow->isActive = false;  // Arrow disappears on hit
                break;  // Stop checking other NPCs
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
