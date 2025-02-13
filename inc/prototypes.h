#pragma once
#include "includs.h"

Vector2* delete_element(Vector2* array, int* size, int index);
Texture2D load_texture(char *file_path);
void draw_info(int w, int m, int f, int s);
void drawWall(int wallX);
bool GetGridCellFromRay(Ray ray, int *cellX, int *cellZ);
Vector3 MoveTowardsParabola(Vector3 current, Vector3 target, float speed, float gravity);
