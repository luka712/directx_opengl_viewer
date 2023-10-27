#version 450 core

in vec3 v_normal;
in vec3 v_fragWorldPos;
in vec3 v_viewDir; // direction towards the camera, from fragment position

layout (std140, binding = 2) uniform MaterialBuffer 
{
    uniform float u_refractionIndex;
};

uniform samplerCube u_cubeTexture;

out vec4 outFragColor;

void main()
{
    // just reverse the vector
    vec3 eyeToFrag = -v_viewDir;
    vec3 reflection = refract(eyeToFrag, v_normal,u_refractionIndex );
    outFragColor = vec4(texture(u_cubeTexture, reflection).rgb, 1.0);
}