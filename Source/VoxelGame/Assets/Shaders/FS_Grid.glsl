#version 450 core

#define PI 3.141592

uniform int   u_cellSize;
uniform uvec2 u_gridSize;
//uniform sampler2D u_texture;

out vec4 fragColor;

void main()
{
    // adapted from https://www.shadertoy.com/view/XtcSzf#
    vec2 fragCoord = gl_FragCoord.xy - u_gridSize.xy * 0.5;
    vec2 coord     = cos(PI / u_cellSize * fragCoord);
	fragColor      = vec4(1.0) - smoothstep(0.95, 1.0, max(coord.x,coord.y)) * 0.5;
}
