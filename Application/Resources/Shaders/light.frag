#version 330 core

layout (location = 0) out vec4 resultColor;

uniform vec3 light_pos;
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
	vec4 textureColor = fs_in.color;
	if (fs_in.textureID > 0.0)
	{
		int textureID = int(fs_in.textureID - 0.5);
		textureColor = fs_in.color * texture(textureArray[textureID], fs_in.uv); 
	}

	vec3 lightColor = vec3(1.0f,1.0f,1.0f);
	float ambientFactor = 0.3f;
	float specularFactor = 0.5f;
	
	vec3 norm = normalize(fs_in.normal);
	vec3 lightDir = normalize(light_pos - fs_in.position.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);
	
	vec3 ambient = ambientFactor * lightColor;
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;
	vec3 specular = specularFactor * pow(max(dot(fs_in.position.xyz, reflectDir), 0.0f), 32) * lightColor;

	resultColor = vec4((ambient + diffuse /*+ specular*/), 1) * textureColor;
}