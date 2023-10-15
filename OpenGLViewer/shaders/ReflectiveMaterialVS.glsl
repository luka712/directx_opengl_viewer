#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal; 

layout (std140, binding = 0) uniform CameraBuffer
{
    uniform mat4 u_projectionViewMatrix;
    uniform vec3 u_eyePosition;
};

layout (std140, binding = 1) uniform ModelBuffer 
{
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix; // normal matrix is transposed inverse of model matrix, for non-uniform scaling
};


out vec3 v_normal;
out vec3 v_fragWorldPos;
out vec3 v_viewDir;

void main()
{
    mat4 modelViewProjectionMatrix = u_projectionViewMatrix * u_modelMatrix;
    gl_Position = modelViewProjectionMatrix * vec4(a_position, 1.0);
    v_normal = normalize(mat3(u_normalMatrix) * a_normal);
    v_fragWorldPos = vec3(u_modelMatrix * vec4(a_position, 1.0));
    v_viewDir = normalize(u_eyePosition - v_fragWorldPos);
}