#version 150

uniform sampler2DRect tex0;
uniform vec4 globalColor;
in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
    outputColor = vec4(texture(tex0, texCoordVarying).gbr, globalColor.a);
}