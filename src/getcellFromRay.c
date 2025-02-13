#include "includs.h"

bool GetGridCellFromRay(Ray ray, int *cellX, int *cellZ) {
    if (ray.direction.y == 0.0f) return false;

    float t = -ray.position.y / ray.direction.y;
    if (t < 0.0f) return false;

    Vector3 hit = {
        ray.position.x + t * ray.direction.x,
        0.0f,
        ray.position.z + t * ray.direction.z
    };

    *cellX = (int)(hit.x / CELL_SIZE + GRID_SIZE / 2);
    *cellZ = (int)(hit.z / CELL_SIZE + GRID_SIZE / 2);

    if (*cellX < 0 || *cellX >= GRID_SIZE || *cellZ < 0 || *cellZ >= GRID_SIZE)
        return false; 

    return true;
}
