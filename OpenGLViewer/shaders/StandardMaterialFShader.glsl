#version 400

in vec2 v_texCoord;

uniform sampler2D u_texture;

out vec4 outFragColor;

void main()
{
    outFragColor = texture(u_texture, v_texCoord) ;
}