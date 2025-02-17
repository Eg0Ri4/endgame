#include "light.h"

// Global list of lights
static Light lights[MAX_LIGHTS];
static int lightCount = 0;

// Function to initialize a light
Light CreateLight(Vector3 position, Color color, float power) {
    Light light;
    light.position = position;
    light.color = color;
    light.power = power;
    return light;
}

// Function to add a light to the list
void AddLight(Light light) {
    if (lightCount < MAX_LIGHTS) {
        lights[lightCount] = light;
        lightCount++;
    } else {
        TraceLog(LOG_WARNING, "Maximum number of lights reached.");
    }
}

// Function to update light shader values for all lights
void UpdateLightShader(Shader shader, Camera3D camera) {
    int lightCountLoc = GetShaderLocation(shader, "lightCount");
    SetShaderValue(shader, lightCountLoc, &lightCount, SHADER_UNIFORM_INT);

    float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
    int viewPosLoc = GetShaderLocation(shader, "viewPosition");
    SetShaderValue(shader, viewPosLoc, cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < lightCount; i++) {
        char lightPosName[32], lightColorName[32], lightPowerName[32];
        sprintf(lightPosName, "lights[%d].position", i);
        sprintf(lightColorName, "lights[%d].color", i);
        sprintf(lightPowerName, "lights[%d].power", i);

        int lightPosLoc = GetShaderLocation(shader, lightPosName);
        int lightColorLoc = GetShaderLocation(shader, lightColorName);
        int lightPowerLoc = GetShaderLocation(shader, lightPowerName);

        float lightPos[3] = { lights[i].position.x, lights[i].position.y, lights[i].position.z };
        float lightCol[4] = {
            (float)lights[i].color.r / 255.0f,
            (float)lights[i].color.g / 255.0f,
            (float)lights[i].color.b / 255.0f,
            1.0f
        };

        SetShaderValue(shader, lightPosLoc, lightPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, lightColorLoc, lightCol, SHADER_UNIFORM_VEC4);
        SetShaderValue(shader, lightPowerLoc, &lights[i].power, SHADER_UNIFORM_FLOAT);
    }
}

