#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec3 a_normal; 
layout(location = 3) in vec3 a_color;

layout (std140, binding = 0) uniform CameraBuffer
{
    uniform mat4 u_projectionViewMatrix;
    uniform vec3 u_eyePosition;
};




uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix; // normal matrix is transposed inverse of model matrix, for non-uniform scaling

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_color;
out vec3 v_fragWorldPos;
out vec3 v_eyePosition;

void main()
{
    mat4 modelViewProjectionMatrix = u_projectionViewMatrix * u_modelMatrix;
    gl_Position = modelViewProjectionMatrix * vec4(a_position, 1.0);
    v_texCoord = a_texCoord;
    v_normal = u_normalMatrix * a_normal;
    v_color = a_color;
    v_fragWorldPos = vec3(u_modelMatrix * vec4(a_position, 1.0));
    v_eyePosition = u_eyePosition;
}