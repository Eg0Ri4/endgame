#include "raylib.h"
#include <math.h>

// Function to move an object towards a target
/*Vector2 MoveTowards(Vector3 current, Vector3 target, float speed) {
    Vector2 direction = { target.x - current.x, target.y - current.y };
    float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

    // If close to the target, stop moving
    if (distance < speed) {
        return target;
    }

    // Normalize direction
    direction.x /= distance;
    direction.y /= distance;

    // Move object
    current.x += direction.x * speed;
    current.y += direction.y * speed;

    return current;
}

Vector3 MoveTowardsParabola(Vector3 current, Vector3 target, float speed, float gravity) {
    // Vector direction from current position to target position
    Vector3 direction = { target.x - current.x, target.y - current.y, target.z - current.z };

    // Calculate horizontal distance (ignoring the y-axis for now)
    float horizontalDistance = sqrtf(direction.x * direction.x + direction.z * direction.z);

    // If close to the target in both x and z directions, stop moving
    if (horizontalDistance < speed) {
        return target;
    }

    // Normalize horizontal direction
    direction.x /= horizontalDistance;
    direction.z /= horizontalDistance;

    // Move horizontally towards the target
    current.x += direction.x * speed;
    current.z += direction.z * speed;

    // Apply a parabolic effect for vertical movement (y-axis)
    float time = horizontalDistance / speed;
    current.y = target.y + gravity * time * time; // Parabolic motion formula for vertical position

    return current;
}
*/
