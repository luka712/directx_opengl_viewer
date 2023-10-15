#version 450 core

#define MAX_DIRECTIONAL_LIGHTS 3
#define MAX_POINT_LIGHTS 5

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_color;
in vec3 v_fragWorldPos;
in vec3 v_viewDir; // direction towards the camera, from fragment position

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
    // attenuation
    float constant;
    float linear;
    float quadratic;
};

struct Material 
{
    // how much of the diffuse color is reflected
    float diffuseCoefficient;
    // how much of the specular color is reflected
    float specularCoefficient;
    float shininess;
};

layout (std140, binding = 3) uniform AmbientLightBuffer
{
    AmbientLight u_ambientLight;
};

layout(std140, binding = 4) uniform DirectionalLightsBuffer 
{
    DirectionalLight u_directionalLight;
};

layout(std140, binding = 5) uniform PointLightsBuffer 
{
    PointLight u_pointLights[MAX_POINT_LIGHTS];
};

layout(std140, binding = 6) uniform MaterialBuffer 
{
    Material u_material;
};

uniform sampler2D u_diffuseTexture;
uniform sampler2D u_specularTexture;


out vec4 outFragColor;

vec3 ambientLight(AmbientLight light, Material material)
{
    return light.intensity * light.color * material.diffuseCoefficient;
}

vec3 directionalDiffuseLight(DirectionalLight light, Material material)
{
    vec3 lightDirection = normalize(-light.direction);
    return light.intensity * light.color * material.diffuseCoefficient * max(dot(lightDirection, v_normal), 0.0);
}

vec3 directionalSpecularLight(DirectionalLight light, Material material)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 halfwayDir = normalize(lightDir + v_viewDir);
    // find specular intensity
    float spec = max(dot(v_normal, halfwayDir), 0.0);
    // calculate final specular color, higher the shininess the more focused the specular highlight is
    spec = pow(spec, material.shininess);
    return light.intensity * material.specularCoefficient * light.color * spec;
}

vec3 pointDiffuseLight(PointLight light, Material material)
{
    vec3 n_direction = normalize(light.position - v_fragWorldPos);
    return light.intensity * light.color * material.diffuseCoefficient * max(dot(v_normal, n_direction), 0.0);
}

vec3 pointSpecularLight(PointLight light, Material material)
{
    vec3 lightDir = normalize(light.position - v_fragWorldPos);
    vec3 halfwayDir = normalize(lightDir + v_viewDir);
    // find specular intensity
    float spec = max(dot(v_normal, halfwayDir), 0.0);
    // calculate final specular color, higher the shininess the more focused the specular highlight is
    spec = pow(spec, material.shininess);
    return light.intensity * material.specularCoefficient * light.color * spec;
}

float pointLightAttenuation(PointLight light, vec3 fragPos)
{
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic* (distance * distance));
    return attenuation;
}

void main()
{
    // Ambient
    vec3 ambient =  ambientLight(u_ambientLight, u_material);

    // Directional
    vec3 directional = directionalDiffuseLight(u_directionalLight, u_material);
    vec3 directionalSpec = directionalSpecularLight(u_directionalLight, u_material);
    
    // Point Lights 
    vec3 point = vec3(0.0);
    vec3 pointSpec = vec3(0.0);
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        PointLight light = u_pointLights[i];

        float a = pointLightAttenuation(light, v_fragWorldPos);

        point += pointDiffuseLight(light, u_material) * a;
        pointSpec += pointSpecularLight(light, u_material) * a;
    }

    // total light
    vec3 lightAmount = ambient + directional + point;
    vec3 specularAmount =  directionalSpec + pointSpec;

    vec3 diffuseColor = texture(u_diffuseTexture, v_texCoord).rgb * lightAmount * v_color;
    vec3 specularColor = texture(u_specularTexture, v_texCoord).rgb * specularAmount * v_color;

    outFragColor = vec4(diffuseColor + specularColor, 1.0);
}