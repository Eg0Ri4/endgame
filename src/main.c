#include "raylib.h"
#include "raymath.h"

/*struct Light{
    Vector3 lightPosition;
    Color lightColor;
    float lightPower = 1.0f;
};*/

void draw_info(int w, int m, int f, double s);
int main(void)
{
    // Initialize window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "3D Lighting Demo");

    // Define camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){80.0f, 60.0f, 80.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load model
    Model model = LoadModel("resources/models/Last-vers-3d.glb"); // Replace with your model path

    // Load lighting shader
    Shader shader = LoadShader(
        "resources/shaders/lighting.vs",
        "resources/shaders/lighting.fs"
    );

    // Assign shader to ALL materials in the model
    for (int i = 0; i < model.materialCount; i++) {
        model.materials[i].shader = shader;
    }

    // Light parameters
    Vector3 lightPosition = {-63.0f, 90.0f, 135.0f };
    Color lightColor = { 255, 214, 170 };
    float lightPower = 1.0f;

    // Get shader locations
    int lightPosLoc = GetShaderLocation(shader, "lightPosition");
    int lightColorLoc = GetShaderLocation(shader, "lightColor");
    int lightPowerLoc = GetShaderLocation(shader, "lightPower");
    int viewPosLoc = GetShaderLocation(shader, "viewPosition");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) lightPosition.x += 1.0f;
        if (IsKeyDown(KEY_LEFT)) lightPosition.x -= 1.0f;
        if (IsKeyDown(KEY_UP)) lightPosition.y -= 1.0f;
        if (IsKeyDown(KEY_DOWN)) lightPosition.y += 1.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT)) lightPosition.z -= 1.0f;
        if (IsKeyDown(KEY_SPACE)) lightPosition.z += 1.0f;
        if (IsKeyDown(KEY_EQUAL)) lightPower += 0.1f;
        if (IsKeyDown(KEY_MINUS)) lightPower -= 0.1f;
        // Update shader values
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        float lightPos[3] = { lightPosition.x, lightPosition.y, lightPosition.z };
        float lightCol[4] = {
            (float)lightColor.r/255.0f,
            (float)lightColor.g/255.0f,
            (float)lightColor.b/255.0f,
            1.0f
        };

        SetShaderValue(shader, viewPosLoc, cameraPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, lightPosLoc, lightPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, lightColorLoc, lightCol, SHADER_UNIFORM_VEC4);
        SetShaderValue(shader, lightPowerLoc, &lightPower, SHADER_UNIFORM_FLOAT);

        // Draw
        BeginDrawing();
            ClearBackground(DARKGRAY);
            
            BeginMode3D(camera);
                DrawModel(model, Vector3Zero(), 1.0f, WHITE); // Draw the model
                DrawSphere(lightPosition, 2.0f, WHITE); // Visualize light position
            EndMode3D();
            draw_info(lightPos[0], lightPos[1], lightPos[2], lightPower);
            DrawFPS(10, 40);
        EndDrawing();
    }

    UnloadModel(model);
    UnloadShader(shader);
    CloseWindow();

    return 0;
}