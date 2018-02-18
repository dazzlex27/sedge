#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);

out DATA
{
	vec3 position;
	vec2 uv;
} vs_out;

void main()
{
	gl_Position =  pr_matrix * vw_matrix * vec4(position, 1.0f);
	vs_out.position = vec3(vec4(position, 1.0f));
	vs_out.uv = uv;
}