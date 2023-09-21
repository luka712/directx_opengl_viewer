#version 400 

layout(location = 0) in vec3 a_position;

uniform mat4 u_projectionViewMatrix;
uniform mat4 u_modelMatrix;

void main()
{
    mat4 modelViewProjectionMatrix = u_projectionViewMatrix * u_modelMatrix;
    gl_Position = modelViewProjectionMatrix * vec4(a_position, 1.0);
}