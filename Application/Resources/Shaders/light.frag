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
	float inCutOff;
	float outCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
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
} fragment;

void main()
{
	// ambient light
	vec3 ambient = light.ambient * texture(material.diffuse, fragment.uv).rgb;
	
	// diffuse color
	vec3 norm = normalize(fragment.normal);
	vec3 lightDir = normalize(light.position - fragment.position);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fragment.uv).rgb;
	
	// specular light
	vec3 viewDir = normalize(viewPos - fragment.position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, fragment.uv).rgb;
	
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.inCutOff - light.outCutOff;
	float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(light.position - fragment.position);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));
	ambient *= attenuation;
	diffuse *=attenuation;
	specular *= attenuation;
	
	resultColor = vec4((ambient + diffuse + specular), 1);
}



////vec4 textureColor = fragment.color;
//	//if (fragment.textureID > 0.0)
//	//{
//	//	int textureID = int(fragment.textureID - 0.5);
//	//	textureColor = fragment.color * texture(textureArray[textureID], fragment.uv); 
//	//}
//
//	float distance = length(light.position - fragment.position);
//	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));
//
//	// ambient light
//	vec3 ambient = light.ambient * texture(material.diffuse, fragment.uv).rgb * attenuation;
//
//	// diffuse color
//	vec3 norm = normalize(fragment.normal);
//	vec3 lightDir = normalize(-light.direction);
//	float diff = max(dot(norm, lightDir), 0.0f);
//	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fragment.uv).rgb * attenuation;
//
//	// specular light
//	vec3 viewDir = normalize(viewPos - fragment.position);
//	vec3 reflectDir = reflect(-lightDir, norm);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
//	vec3 specular = light.specular * spec * texture(material.specular, fragment.uv).rgb * attenuation;
//
//	resultColor = vec4((ambient + diffuse + specular), 1);// * textureColor;