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
void UpdateLightShader(Light light, Shader shader, Camera3D camera) {
    int lightPosLoc = GetShaderLocation(shader, "lightPosition");
    int lightColorLoc = GetShaderLocation(shader, "lightColor");
    int lightPowerLoc = GetShaderLocation(shader, "lightPower");
    int viewPosLoc = GetShaderLocation(shader, "viewPosition");

    float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
    float lightPos[3] = { light.position.x, light.position.y, light.position.z };
    float lightCol[4] = {
        (float)light.color.r / 255.0f,
        (float)light.color.g / 255.0f,
        (float)light.color.b / 255.0f,
        1.0f
    };

    SetShaderValue(shader, viewPosLoc, cameraPos, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, lightPosLoc, lightPos, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, lightColorLoc, lightCol, SHADER_UNIFORM_VEC4);
    SetShaderValue(shader, lightPowerLoc, &light.power, SHADER_UNIFORM_FLOAT);
}

// Function to draw light information
void DrawLightInfo(Light light) {
    DrawText(TextFormat("Light Position: (%.1f, %.1f, %.1f)", light.position.x, light.position.y, light.position.z), 10, 10, 20, WHITE);
    DrawText(TextFormat("Light Power: %.1f", light.power), 10, 30, 20, WHITE);
}
