#pragma once
#include "includs.h"

#define MAX_LIGHTS 5

typedef struct {
    Vector3 position;
    Color color;
    float power;
} Light;

void AddLight(Light light);
void UpdateLightShader(Shader shader, Camera3D camera);
void HandleLightInput(Light *light);
Light CreateLight(Vector3 position, Color color, float power);
