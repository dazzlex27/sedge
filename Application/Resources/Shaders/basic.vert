#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;
layout (location = 4) in float textureID;

uniform mat4 ml_matrix = mat4(1.0f);
uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);

out DATA
{
	vec3 position;
	vec4 color;
	vec3 normal;
	vec2 uv;
	float textureID;
} vs_out;

void main()
{
	gl_Position =  pr_matrix * vw_matrix * ml_matrix * vec4(position, 1.0f);
	vs_out.position = vec3(ml_matrix * vec4(position, 1.0f));
	vs_out.color = color;
	vs_out.normal = normal;
	vs_out.uv = uv;
	vs_out.textureID = textureID;
}