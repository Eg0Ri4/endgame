#pragma once
#include "includs.h"

#define MAX_LIGHTS 3
// Light structure
typedef struct {
    Vector3 position;
    Color color;
    float power;
} Light;

void UpdateLightShader(Light lights[], int numLights, Shader shader, Camera3D camera);
void HandleLightInput(Light *light);
void DrawLightInfo(Light light);
void ModifyLight(Light *light, Vector3 position, Color color, float power);
void RemoveLight(Light lights[], int *numActiveLights, int index);
Light CreateLight(Vector3 position, Color color, float power);
void AddLight(Light lights[], int *numActiveLights, Vector3 position, Color color, float power);

