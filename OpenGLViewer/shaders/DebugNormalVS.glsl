#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal; 

out vec3 v_normal;


void main()
{
    gl_Position = vec4(a_position, 1.0);
    v_normal = a_normal;
}