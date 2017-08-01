#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 lightPos;
uniform sampler2D textureArray[32];

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
	vec4 textureColor = fs_in.color;
	if (fs_in.textureID > 0.0)
	{
		int textureID = int(fs_in.textureID - 0.5);
		textureColor = fs_in.color * texture(textureArray[textureID], fs_in.uv); 
	}

	color = textureColor;
}