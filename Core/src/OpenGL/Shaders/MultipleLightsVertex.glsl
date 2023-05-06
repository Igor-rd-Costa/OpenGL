#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;

void main()
{
	gl_Position = ProjMatrix * ViewMatrix * ModelMatrix * vec4(aPosition, 1.0);

	FragPos = vec3(ModelMatrix * vec4(aPosition, 1.0));
	Normal = mat3(transpose(inverse(ModelMatrix))) *  aNormal;
	TexCoord = aTexCoord;
}