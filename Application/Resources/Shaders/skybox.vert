#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 ml_matrix = mat4(1.0f);
uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);

void main()
{
	gl_Position =  pr_matrix * vw_matrix * ml_matrix * vec4(position, 1.0f);
}