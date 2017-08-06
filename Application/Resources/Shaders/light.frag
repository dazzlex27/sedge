#version 330 core

layout (location = 0) out vec4 resultColor;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light 
{
    vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;
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

	// ambient light
	vec3 ambient = light.ambient * texture(material.diffuse, fs_in.uv).rgb;

	// diffuse color
	vec3 norm = normalize(fs_in.normal);
	vec3 lightDir = normalize(light.position - fs_in.position);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fs_in.uv).rgb;

	// specular light
	vec3 viewDir = normalize(viewPos - fs_in.position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, fs_in.uv).rgb;

	resultColor = vec4((ambient + diffuse + specular), 1);// * textureColor;
}