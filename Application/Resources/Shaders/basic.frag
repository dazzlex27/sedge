#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform sampler2D textureArray[32];

in DATA
{
	vec4 position;
	vec4 color;
	vec3 normal;
	vec2 uv;
	float textureID;
} fs_in;


void main()
{
	float ambientFactor = 0.1f;
	vec3 ambient = ambientFactor * vec3(1.0f,1.0f,1.0f);

	vec4 textureColor = fs_in.color;
	if (fs_in.textureID > 0.0)
	{
		int textureID = int(fs_in.textureID - 0.5);
		textureColor = fs_in.color * texture(textureArray[textureID], fs_in.uv); 
	}

	color = ambient * textureColor;
}