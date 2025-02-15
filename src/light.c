#include "includs.h"

// Function to initialize a light
Light CreateLight(Vector3 position, Color color, float power) {
    Light light;
    light.position = position;
    light.color = color;
    light.power = power;
    return light;
}

// Function to update light shader values
void UpdateLightShader(Light lights[], int numLights, Shader shader, Camera3D camera) {
    int numLightsLoc = GetShaderLocation(shader, "numLights");
    int viewPosLoc = GetShaderLocation(shader, "viewPosition");

    // Pass the number of lights
    SetShaderValue(shader, numLightsLoc, &numLights, SHADER_UNIFORM_INT);

    // Convert camera position to float array
    float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
    SetShaderValue(shader, viewPosLoc, cameraPos, SHADER_UNIFORM_VEC3);

    // Loop through all lights and pass their values to the shader
    for (int i = 0; i < numLights; i++) {
        char uniformName[64];  // Buffer to store uniform name string

        // Light Position
        snprintf(uniformName, sizeof(uniformName), "lights[%d].position", i);
        int lightPosLoc = GetShaderLocation(shader, uniformName);
        float lightPos[3] = { lights[i].position.x, lights[i].position.y, lights[i].position.z };
        SetShaderValue(shader, lightPosLoc, lightPos, SHADER_UNIFORM_VEC3);

        // Light Color
        snprintf(uniformName, sizeof(uniformName), "lights[%d].color", i);
        int lightColorLoc = GetShaderLocation(shader, uniformName);
        float lightCol[4] = {
            lights[i].color.r / 255.0f,
            lights[i].color.g / 255.0f,
            lights[i].color.b / 255.0f,
            1.0f
        };
        SetShaderValue(shader, lightColorLoc, lightCol, SHADER_UNIFORM_VEC4);

        // Light Power
        snprintf(uniformName, sizeof(uniformName), "lights[%d].power", i);
        int lightPowerLoc = GetShaderLocation(shader, uniformName);
        SetShaderValue(shader, lightPowerLoc, &lights[i].power, SHADER_UNIFORM_FLOAT);
    }
}

void AddLight(Light lights[], int *numActiveLights, Vector3 position, Color color, float power) {
    if (*numActiveLights >= MAX_LIGHTS) {
        return;  // No space left in the array
    }

    // Add the new light
    lights[*numActiveLights] = CreateLight(position, color, power);
    (*numActiveLights)++;  // Increment the number of active lights
}

void RemoveLight(Light lights[], int *numActiveLights, int index) {
    if (index < 0 || index >= *numActiveLights) {
        return;  // Invalid index
    }

    // Shift all lights after the removed light to the left
    for (int i = index; i < *numActiveLights - 1; i++) {
        lights[i] = lights[i + 1];
    }

    (*numActiveLights)--;  // Decrement the number of active lights
}

void ModifyLight(Light *light, Vector3 position, Color color, float power) {
    light->position = position;
    light->color = color;
    light->power = power;
}
// Function to draw light information
void DrawLightInfo(Light light) {
    DrawText(TextFormat("Light Position: (%.1f, %.1f, %.1f)", light.position.x, light.position.y, light.position.z), 10, 10, 20, WHITE);
    DrawText(TextFormat("Light Power: %.1f", light.power), 10, 30, 20, WHITE);
}
