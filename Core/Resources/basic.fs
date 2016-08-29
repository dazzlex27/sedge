#version 450 core

layout (location = 0) out vec4 color;
in vec3 fragmentColor;

in vec4 pos;

uniform vec4 cl;
uniform vec2 light_pos;

void main()
{
	color = vec4(fragmentColor.x,fragmentColor.y,fragmentColor.z,1);
	//float intensity = 1.0f / length(pos.xy - light_pos);
	//color = cl;// * intensity;
}