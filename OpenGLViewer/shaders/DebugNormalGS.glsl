#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in vec3 v_normal[];

const float MAGNITUDE = 0.5;

layout (std140, binding = 0) uniform ProjectionBuffer 
{
    uniform mat4 u_projectionMatrix;
};

layout (std140, binding = 1) uniform ViewModelBuffer 
{
    uniform mat4 u_viewModelMatrix;
    uniform mat4 u_viewModelNormalMatrix;
};



void generateLine(int index)
{
    // start 
    vec4 viewSpacePos = u_viewModelMatrix * gl_in[index].gl_Position;
    gl_Position = u_projectionMatrix * viewSpacePos;
    EmitVertex();

    // end 
    vec4 normal = normalize(u_viewModelNormalMatrix * vec4(v_normal[index], 0.0)) * MAGNITUDE;
    // note: we add the normal to the view space position to get the end point
    gl_Position = u_projectionMatrix * (viewSpacePos + normal);
    EmitVertex();

    EndPrimitive();
}

void main()
{
    generateLine(0);
    generateLine(1);
    generateLine(2);
}