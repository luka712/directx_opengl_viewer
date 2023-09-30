#version 400

#define MAX_DIRECTIONAL_LIGHTS 3

in vec2 v_texCoord;
in vec3 v_normal;

struct AmbientLight 
{
    float intensity;
    vec3 color;
};

struct DirectionalLight 
{
    vec3 direction;
    float intensity;
    vec3 color;
};

uniform sampler2D u_texture;

uniform AmbientLight u_ambientLight;
uniform DirectionalLight u_directionalLights[MAX_DIRECTIONAL_LIGHTS];

out vec4 outFragColor;

void main()
{
    vec4 matColor = texture(u_texture, v_texCoord);

    // Ambient
    vec3 ambient = u_ambientLight.intensity * u_ambientLight.color;

    // Directional
    vec3 directional = vec3(0.0);
    vec3 n_normal = normalize(v_normal);
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
    {
        DirectionalLight light = u_directionalLights[i];
        vec3 n_direction = normalize(-light.direction);

        directional += light.intensity * light.color * max(dot(n_normal, n_direction), 0.0);
    }

    // total light
    vec3 lightAmount = ambient * 0.01 + directional;

    outFragColor = vec4(matColor.rgb * lightAmount, matColor.a);
}