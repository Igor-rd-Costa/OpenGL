#include "ShaderProgram.h"
#include "GL/glew.h"

#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <Windows.h>
namespace Core {


uint32_t* ShaderIDs::begin()
{
	return &VertShaderID;
}
uint32_t* ShaderIDs::end()
{
	return &FragShaderID + 1;
}




ShaderProgram::ShaderProgram()
	:m_Shaders({ 0, 0 })
{
	m_ProgramID = glCreateProgram();
BindingPoints.fill(-1);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ProgramID);
}

ShaderProgram::ShaderProgram(const std::string& VertexSource, const std::string& FragmentSource)
{
	m_ProgramID = glCreateProgram();
BindingPoints.fill(-1);
	if (AttachShader(VertexSource, GL_VERTEX_SHADER) && AttachShader(FragmentSource, GL_FRAGMENT_SHADER))
	{
		this->Link();
	}
}


bool ShaderProgram::AttachShader(const std::string& Source, uint32_t ShaderType)
{
	std::ifstream file(Source);

	if (!file.is_open())
	{
		std::cout << "[OpenGL Shader]Error: Failed to open file " << Source << "." << std::endl;
		return false;
	}
	else
	{
		std::stringstream ss;
		std::string string;
		while (getline(file, string))
		{
			ss << string << "\n";
		}

		string = ss.str();
		const char* Source = string.c_str();

		uint32_t ShaderID = glCreateShader(ShaderType);
		glShaderSource(ShaderID, 1, &Source, nullptr);
		glCompileShader(ShaderID);

		GLint isCompiled = 0;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint LogSize = 0;
			glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &LogSize);

			std::vector<GLchar> ErrorLog(5000);
			glGetShaderInfoLog(ShaderID, LogSize, &LogSize, &ErrorLog[0]);

			string = ErrorLog.data();
			std::cout << "[OpenGL ShaderProgram]Error: " << string << std::endl;
			glDeleteShader(ShaderID);
			return false;
		}

		switch (ShaderType)
		{
		case GL_VERTEX_SHADER: m_Shaders.VertShaderID = ShaderID; 
			break;
		case GL_FRAGMENT_SHADER: m_Shaders.FragShaderID = ShaderID;
			break;
		}
		
		glAttachShader(m_ProgramID, ShaderID);
		return true;
	}
}

void ShaderProgram::Link()
{
	glLinkProgram(m_ProgramID);

	for (const uint32_t& ShaderID : m_Shaders)
	{
		glDetachShader(m_ProgramID, ShaderID);
		glDeleteShader(ShaderID);
	}
}

void ShaderProgram::Bind() const
{
	glUseProgram(m_ProgramID);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix) const
{
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, &Matrix[0][0]);
}

void ShaderProgram::SetUniform1f(const std::string& Name, float Value) const
{
	glUniform1f(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetUniform2f(const std::string& Name, const glm::vec2& Vec2) const
{
	glUniform2f(GetUniformLocation(Name), Vec2.x, Vec2.y);
}

void ShaderProgram::SetUniform3f(const std::string& Name, const glm::vec3& Vec3) const
{
	glUniform3f(GetUniformLocation(Name), Vec3.x, Vec3.y, Vec3.z);
}

void ShaderProgram::SetUniform4f(const std::string& Name, const glm::vec4& Vec4) const
{
	glUniform4f(GetUniformLocation(Name), Vec4.x, Vec4.y, Vec4.z, Vec4.w);
}

void ShaderProgram::SetUniform1i(const std::string& Name, int Value) const
{
	glUniform1i(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetUniform1ui(const std::string& Name, uint32_t Value) const
{
	glUniform1ui(GetUniformLocation(Name), Value);
}

void ShaderProgram::SetUniform1iv(const std::string& Name, int Count, int* Value) const
{
	glUniform1iv(GetUniformLocation(Name), Count, Value);
}

int32_t ShaderProgram::GetUniformBindingPoint()
{
for (int x= 0; x < UsedBindingPoints.size(); x++) {
if(UsedBindingPoints[x] == -1) {
UsedBindingPoints[x] = x;
return x;
}
}
return -1;
}

int ShaderProgram::GetUniformLocation(const std::string& Name) const
{
	if (m_UniformLacationCache.find(Name) != m_UniformLacationCache.end())
		return m_UniformLacationCache[Name];

	int location = glGetUniformLocation(m_ProgramID, Name.c_str());

	if (location == -1)
	{
		return -1;
	}
	else
	{
		m_UniformLacationCache[Name] = location;
		return location;
	}
}

}





