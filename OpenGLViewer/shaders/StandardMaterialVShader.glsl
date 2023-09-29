#version 400 

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_projectionViewMatrix;
uniform mat4 u_modelMatrix;

out vec2 v_texCoord;
out vec4 v_color;

void main()
{
    mat4 modelViewProjectionMatrix = u_projectionViewMatrix * u_modelMatrix;
    gl_Position = modelViewProjectionMatrix * vec4(a_position, 1.0);
    v_texCoord = a_texCoord;
}