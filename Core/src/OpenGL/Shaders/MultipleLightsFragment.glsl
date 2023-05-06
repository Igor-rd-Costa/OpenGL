#version 460 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	int alpha;
};

struct DirectLight {
	bool on;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	bool on;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	bool on;
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
};

vec3 CalculateDirectionalLight(in DirectLight dirLight, in vec3 normal,  in vec3 viewDir);
vec3 CalculatePointLight(in PointLight light, in vec3 normal, in vec3 fragPos, in vec3 viewDirection);
vec3 CalculateSpotLight(in SpotLight light, in vec3 normal, in vec3 fragPos, in vec3 viewDirection);

layout (location = 0) out vec4 Color;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform Material material;
uniform DirectLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform vec3 ViewPos;

void main()
{
	vec3 result = vec3(0.0);
	vec3 viewDir = normalize(ViewPos - FragPos);
	if(dirLight.on)
		result += CalculateDirectionalLight(dirLight, Normal, viewDir);
	if(pointLight.on)
		result += CalculatePointLight(pointLight, Normal, FragPos, viewDir);
	if(spotLight.on)
		result += CalculateSpotLight(spotLight, Normal, FragPos, viewDir);

	Color = vec4(result, material.alpha);
}

vec3 CalculateDirectionalLight(in DirectLight light, in vec3 normal, in vec3 viewDirection)
{
	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	
	vec3 Norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(Norm, lightDir), 0.0);
	vec3 Diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	
	vec3 reflectDir = reflect(-lightDir, Norm);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 128 * material.shininess);
	vec3 Specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	return (Ambient + Diffuse + Specular);
}

vec3 CalculatePointLight(in PointLight light, in vec3 normal, in vec3 fragPos, in vec3 viewDirection)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 Norm = normalize(normal);
	
	float diff = max(dot(Norm, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, Norm);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 128 * material.shininess);
	
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 Diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 Specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	Ambient *= attenuation;
	Diffuse *= attenuation;
	Specular *= attenuation;

	return (Ambient + Diffuse + Specular);
}

vec3 CalculateSpotLight(in SpotLight light, in vec3 normal, in vec3 fragPos, in vec3 viewDirection)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 Norm = normalize(normal);
	
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	float diff = max(dot(Norm, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, Norm);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 128 * material.shininess);
	
	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 Diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 Specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	Diffuse *= intensity;
	Specular *= intensity;

	return (Ambient + Diffuse + Specular);
}