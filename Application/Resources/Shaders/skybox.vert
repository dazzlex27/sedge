#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 uv;

out vec3 sbUV;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);

void main()
{
	sbUV =  uv;
	gl_Position =  pr_matrix * mat4(mat3(vw_matrix)) * vec4(position, 1.0f);
}