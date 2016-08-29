#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

uniform mat4 ml_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 pr_matrix = mat4(1.0);

out vec4 pos;

void main()
{
	gl_Position =  pr_matrix * vw_matrix * ml_matrix * position;
	pos = position;
	fragmentColor = vertexColor;
}