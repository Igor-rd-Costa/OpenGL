#version 460 core

layout (location = 0) in vec3 Positions;
layout (location = 1) in vec3 Normals;
layout (location = 2) in vec2 TexCoords;

out vec3 f_Normals;
out vec2 f_TexCoords;
out vec3 f_FragPos;
out vec3 f_Position;

uniform mat4 ProjMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
	f_TexCoords = TexCoords;
	gl_Position = ProjMatrix * ViewMatrix * ModelMatrix * vec4(Positions, 1.0);
	f_FragPos = vec3(ModelMatrix * vec4(Positions, 1.0));
	f_Normals = mat3(transpose(inverse(ModelMatrix))) * Normals;
	f_Position = Positions;
}