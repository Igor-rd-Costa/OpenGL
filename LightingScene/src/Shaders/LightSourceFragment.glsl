#version 460 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	int alpha;
};


layout(location = 0) out vec4 Color;

in vec3 f_Position;
in vec3 f_Normals;
in vec2 f_TexCoords;

uniform Material material;

void main()
{
	float distance = 1.0 - length(f_Position);
	Color = texture(material.diffuse, f_TexCoords) * vec4(vec3(distance + 0.5), 1.0f);
	Color *= vec4(1.0, 1.0, 1.0, material.alpha);
}