#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform sampler2D tex;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
} fs_in;


void main()
{
	float intensity = 1.0f / length(fs_in.position.xy - light_pos);
	color = texture(tex,fs_in.uv) * intensity;//fs_in.color * intensity;
}