#version 450 core

uniform sampler2D u_texture;
uniform uvec2     u_tileCoords;
uniform uvec2     u_tileSize;
uniform vec2      u_sheetSize;

in VS_OUT
{
    vec2 pos;
    vec2 uv;
    vec3 color;
} vs_in;

out vec4 fragColor;

vec2 getTileUV()
{
    vec2 uv;
   // vec2 scale = vec2(1.0f / u_tileSize.x, 1.0f / u_tileSize.y);
    uv.x = (vs_in.uv.x + u_tileCoords.x) * u_tileSize.x / u_sheetSize.x; //(vs_in.uv.x + u_tileCoords.x) * scale.x;
    uv.y = (vs_in.uv.y + u_tileCoords.y) * u_tileSize.y / u_sheetSize.y; //(vs_in.uv. + u_tileCoords.y) * scale.y;
    return uv;
}

void main()
{
    fragColor = texture2D(u_texture, getTileUV());
}
