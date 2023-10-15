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
    vec4 pos = u_projectionViewMatrix * vec4(a_position, 1.0);
    gl_Position = pos.xyww;
}  