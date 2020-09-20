#version 450 core

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TexCoord;

uniform vec3 Color;
uniform vec2 Offset = { 0.f, 0.f };

out VS_OUT
{
    vec2 pos;
    vec2 uv;
    vec3 color;
} vertex;

void main()
{
    vertex.pos   = Position + Offset;
    vertex.uv    = TexCoord;
    vertex.color = Color;
    gl_Position  = vec4(vertex.pos, 0.0, 1.0);
};
