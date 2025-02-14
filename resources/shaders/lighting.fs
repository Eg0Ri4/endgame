#version 330

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform sampler2D texture0; // Texture for the material
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform float lightPower;

void main()
{
    // Normalize the normal
    vec3 normal = normalize(fragNormal);

    // Light direction
    vec3 lightDir = normalize(lightPosition - fragPosition);

    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor.rgb;

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb * lightPower;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor.rgb * lightPower;

    // Sample texture
    vec4 texColor = texture(texture0, fragTexCoord);

    // Combine lighting with texture
    vec3 result = (ambient + diffuse + specular) * texColor.rgb;
    finalColor = vec4(result, texColor.a);
}