#version 330 core

layout (location = 0) out vec4 resultColor;

struct Material 
{
    sampler2D diffuse;
	sampler2D specular;
    float shininess;
}; 

struct DirLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight 
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight 
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
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform Material material;

in DATA
{
	vec3 position;
	vec4 color;
	vec3 normal;
	vec2 uv;
} fragment;

vec3 GetDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 GetPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 GetSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 norm = normalize(fragment.normal);
	vec3 viewDir = normalize(viewPos - fragment.position);

	vec3 dirLight = GetDirLight(dirLight, norm, viewDir);
	//vec3 pointLight = GetPointLight(pointLight, norm, viewDir);
	//vec3 spotLight = GetSpotLight(spotLight, norm, viewDir);
	
	vec3 result = dirLight;// + pointLight + spotLight;
	
	resultColor = vec4(result, 1);
}

vec3 GetDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient * texture(material.diffuse, fragment.uv).rgb;

	vec3 lightDir = normalize(light.direction);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fragment.uv).rgb;
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, fragment.uv).rgb;
	
	return ambient + diffuse + specular;
}

vec3 GetPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient * texture(material.diffuse, fragment.uv).rgb;
	
	vec3 lightDir = normalize(light.position - fragment.position);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fragment.uv).rgb;
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, fragment.uv).rgb;

	float distance = length(light.position - fragment.position);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));
	ambient *= attenuation;
	diffuse *=attenuation;
	specular *= attenuation;
	
	return ambient + diffuse + specular;
}

vec3 GetSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient * texture(material.diffuse, fragment.uv).rgb;
	
	vec3 lightDir = normalize(light.position - fragment.position);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fragment.uv).rgb;
	
	vec3 reflectDir = reflect(-lightDir, normal);
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
	
	return ambient + diffuse + specular;
}