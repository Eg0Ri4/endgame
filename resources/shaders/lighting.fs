#version 330

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

// Uniforms for texture and lighting
uniform sampler2D texture0;  // Texture for the material
uniform vec3 viewPosition;   // Camera/view position

// Lighting parameters
uniform float ambientStrength;  // Ambient strength (default: 0.1)
uniform float specularStrength; // Specular strength (default: 0.5)

// Define max number of lights
#define MAX_LIGHTS 10  // Adjust this based on your needs

// Light structure
struct Light {
    vec3 position;
    vec4 color;
    float power;
};

// Uniform array of lights
uniform Light lights[MAX_LIGHTS];  // Array of lights
uniform int numLights;             // Number of lights in the scene

void main()
{
    // Normalize the normal
    vec3 normal = normalize(fragNormal);
    vec3 result = vec3(0.0);

    // Loop through all the lights
    for (int i = 0; i < numLights; i++) {
        // Light direction
        vec3 lightDir = normalize(lights[i].position - fragPosition);

        // Ambient lighting
        vec3 ambient = ambientStrength * lights[i].color.rgb;

        // Diffuse lighting
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color.rgb * lights[i].power;

        // Specular lighting
        vec3 viewDir = normalize(viewPosition - fragPosition);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lights[i].color.rgb * lights[i].power;

        // Accumulate the lighting contributions from each light
        result += ambient + diffuse + specular;
    }

    // Sample texture
    vec4 texColor = texture(texture0, fragTexCoord);

    // Combine lighting with texture
    finalColor = vec4(result * texColor.rgb, texColor.a);
}
