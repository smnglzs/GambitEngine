#version 450 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoord;

// uniform mat3 Projection;
uniform vec3  u_color;
uniform vec2  u_offset;
uniform mat4  u_model;
uniform mat4  u_projection;

layout(std140, binding = 0) uniform TransformBlock
{
    vec2 scale;
    vec2 translation;
    vec2 rotation;
} transform;

out VS_OUT
{
    vec2 pos;
    vec2 uv;
    vec3 color;
} vs_out;

void main()
{
    vs_out.pos   = (u_projection * u_model * vec4(a_position, 0.0, 1.0)).xy;
    vs_out.uv    = a_texCoord;
    vs_out.color = u_color;

    gl_Position  = vec4(vs_out.pos, 0.0, 1.0);
};
