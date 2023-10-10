#version 450 core

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_color;

struct Material 
{
    vec3 diffuseColor;
    float intensity;
};

layout(std140, binding = 3) uniform MaterialBuffer 
{
    Material u_material;
};

uniform sampler2D u_diffuseTexture;

out vec4 outFragColor;

void main()
{
    vec4 texColor = texture(u_diffuseTexture, v_texCoord);
    outFragColor = vec4(texture(u_diffuseTexture, v_texCoord).rgb *  v_color * u_material.diffuseColor * u_material.intensity, 1.0);
}