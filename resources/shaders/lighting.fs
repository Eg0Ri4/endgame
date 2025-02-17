#version 330

// Maximum number of lights
#define MAX_LIGHTS 10

// Light structure
struct Light {
    vec3 position;
    vec4 color;
    float power;
};

// Inputs from the vertex shader
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;
in vec4 fragColor;

// Uniforms
uniform int lightCount;               // Number of active lights
uniform Light lights[MAX_LIGHTS];     // Array of lights
uniform vec3 viewPosition;            // Camera position
uniform sampler2D texture0;           // Texture (optional)

// Output color
out vec4 finalColor;

void main() {
    // Normalize the fragment normal
    vec3 normal = normalize(fragNormal);

    // View direction (from fragment to camera)
    vec3 viewDir = normalize(viewPosition - fragPosition);

    // Base color (from texture or vertex color)
    vec4 texColor = texture(texture0, fragTexCoord);
    vec4 baseColor = texColor * fragColor;

    // Initialize lighting contribution
    vec3 lighting = vec3(0.0);

    // Loop through all lights
    for (int i = 0; i < lightCount; i++) {
        // Light direction (from fragment to light)
        vec3 lightDir = normalize(lights[i].position - fragPosition);

        // Diffuse component
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = lights[i].color.rgb * diff * lights[i].power;

        // Add diffuse contribution to lighting
        lighting += diffuse;
    }

    // Combine base color with lighting
    finalColor = vec4(lighting, 1.0) * baseColor;
}