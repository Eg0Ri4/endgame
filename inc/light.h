#pragma once
#include "includs.h"

// Light structure
typedef struct {
    Vector3 position;
    Color color;
    float power;
} Light;

void UpdateLightShader(Light light, Shader shader, Camera3D camera);
void HandleLightInput(Light *light);
void DrawLightInfo(Light light);
Light CreateLight(Vector3 position, Color color, float power);
