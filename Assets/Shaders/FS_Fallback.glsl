#version 450 core

uniform float     Time;
uniform sampler2D Texture;
uniform ivec2     ScreenSize;

in VS_OUT
{
    vec2 pos;
    vec2 uv;
    vec3 color;
} vertex;

out vec4 fragmentColor;

void main()
{
    float g = abs(sin(Time));
    float b = abs(cos(Time));
    fragmentColor = mix(vec4(gl_FragCoord.x / ScreenSize.x, g, b, 1.0), texture2D(Texture, vertex.uv), 0.5);
}
