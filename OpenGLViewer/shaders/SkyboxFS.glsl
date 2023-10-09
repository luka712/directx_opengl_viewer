#version 450 core

in vec3 v_texCoords;

uniform samplerCube u_cubeTexture;

out vec4 outFragColor;

void main()
{    
    outFragColor = texture(u_cubeTexture, v_texCoords);
}