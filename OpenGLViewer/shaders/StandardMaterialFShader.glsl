#version 450 core

#define MAX_DIRECTIONAL_LIGHTS 3
#define MAX_POINT_LIGHTS 5

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_color;
in vec3 v_fragWorldPos;

struct AmbientLight 
{
    vec3 color;
    float intensity;
};

struct DirectionalLight 
{
    vec3 direction;
    float intensity;
    vec3 color;
};

struct PointLight 
{
    vec3 position;
    float intensity;
    vec3 color;
};

struct Material 
{
    // how much of the diffuse color is reflected
    float diffuseCoefficient;
    // how much of the specular color is reflected
    float specularCoefficient;
    float shininess;
};

layout (std140, binding = 0) uniform AmbientLightBuffer
{
    AmbientLight u_ambientLight;
};

layout(std140, binding = 1) uniform DirectionalLightsBuffer 
{
    DirectionalLight u_directionalLights[MAX_DIRECTIONAL_LIGHTS];
};

layout(std140, binding = 2) uniform PointLightsBuffer 
{
    PointLight u_pointLights[MAX_POINT_LIGHTS];
};

layout(std140, binding = 3) uniform MaterialBuffer 
{
    Material u_material;
};

uniform sampler2D u_diffuseTexture;
uniform sampler2D u_specularTexture;

uniform vec3 u_cameraPosition;

out vec4 outFragColor;

vec3 ambientLight(AmbientLight light, Material material)
{
    return light.intensity * light.color * material.diffuseCoefficient;
}

vec3 directionalDiffuseLight(DirectionalLight light, Material material, vec3 normal)
{
    vec3 lightDirection = normalize(-light.direction);
    return light.intensity * light.color * material.diffuseCoefficient * max(dot(lightDirection, normal), 0.0);
}

vec3 directionalSpecularLight(DirectionalLight light, Material material, vec3 normal)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 viewDir = normalize(u_cameraPosition - v_fragWorldPos);
    vec3 halfwayDir= normalize(lightDir + viewDir);
    // find specular intensity
    float spec = max(dot(normal, halfwayDir), 0.0);
    // calculate final specular color, higher the shininess the more focused the specular highlight is
    spec = pow(spec, material.shininess);
    return light.intensity * material.specularCoefficient * light.color * spec;
}

vec3 pointDiffuseLight(PointLight light, Material material, vec3 normal)
{
    vec3 n_direction = normalize(light.position - v_fragWorldPos);
    return light.intensity * light.color * material.diffuseCoefficient * max(dot(normal, n_direction), 0.0);
}

void main()
{
    // Ambient
    vec3 ambient =  ambientLight(u_ambientLight, u_material);

    // Directional
    vec3 directional = vec3(0.0);
    vec3 directionalSpec = vec3(0.0);
    vec3 n_normal = normalize(v_normal);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++) 
    {
        // Diffuse
        DirectionalLight light = u_directionalLights[i];

        directional += directionalDiffuseLight(light, u_material, n_normal);
        directionalSpec += directionalSpecularLight(light, u_material, n_normal);
    }

    // Point Lights 
    vec3 point = vec3(0.0);
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        PointLight light = u_pointLights[i];
        point += pointDiffuseLight(light, u_material, n_normal);
    }

    // total light
    vec3 lightAmount = ambient + directional + point;
    vec3 specularAmount = directionalSpec;

    vec3 diffuseColor = texture(u_diffuseTexture, v_texCoord).rgb * lightAmount * v_color;
    vec3 specularColor = texture(u_specularTexture, v_texCoord).rgb * specularAmount * v_color;

    outFragColor = vec4(diffuseColor + specularColor, 1.0);
}