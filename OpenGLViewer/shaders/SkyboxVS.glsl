#version 450 core

layout(location = 0) in vec3 a_position;

out vec3 v_texCoords;

layout (std140, binding = 0) uniform CameraBuffer
{
    uniform mat4 u_projectionViewMatrix;
};

void main()
{
    v_texCoords = a_position;
    gl_Position = u_projectionViewMatrix * vec4(a_position, 1.0);
}  