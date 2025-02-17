#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec4 vertexColor;

// Outputs to the fragment shader
out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;
out vec4 fragColor;

// Uniforms (matrices)
uniform mat4 mvp;        // Model-View-Projection matrix
uniform mat4 matModel;   // Model matrix
uniform mat4 matNormal;  // Normal matrix

void main() {
    // Calculate vertex position in world space
    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));

    // Transform the normal using the normal matrix
    fragNormal = normalize(vec3(matNormal * vec4(vertexNormal, 1.0)));

    // Pass texture coordinates and color to the fragment shader
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    // Calculate final vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}