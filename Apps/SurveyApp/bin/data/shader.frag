#version 150

uniform sampler2DRect tex0;
uniform vec4 globalColor;
uniform float Answer; // 1 = yes, -1 = no, 0 = undecided
uniform float Center;
in vec2 texCoordVarying;
out vec4 outputColor;

// Adapted from https://www.shadertoy.com/view/Xscyzn
// ShaderToy test https://www.shadertoy.com/view/wsfSRr

#define PI 3.14159

void main()
{
    vec2 texDim = textureSize(tex0);
    float effectRadius = 1.0;
    float effectAngle = 2.0 * Answer * PI;
    float yes = smoothstep(0.0,  1.0, Answer);
    float no  = smoothstep(0.0, -1.0, Answer);
    vec2 center = vec2(Center, .5);
    vec2 uv = texCoordVarying/texDim - center;

    float len = length(uv);
    float angle = atan(uv.y, uv.x) + effectAngle * smoothstep(effectRadius, 0., len);
    float radius = length(uv);
    vec2 twistUV = radius * vec2(cos(angle), sin(angle)) + center;

    // Mirror repeat the texture coordinates
    twistUV = 2.0*abs(round(0.5*twistUV)-0.5*twistUV);

    vec3 camCol = texture(tex0, twistUV*texDim).rgb;
    vec3 col = camCol;
    col.gb -= yes*camCol.gb;
    col.rb -= no*camCol.rb;
    outputColor = vec4(col, globalColor.a);
}