#version 330 core

out vec4 outColor;

uniform sampler2D tex;

in DATA
{
	vec3 position;
	vec4 color;
	vec3 normal;
	vec2 uv;
	float textureID;
} fs_in;


void main()
{
	outColor = texture(tex, fs_in.uv);
}