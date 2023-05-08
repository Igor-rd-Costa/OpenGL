#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

namespace Core {

struct ShaderIDs
{
	uint32_t VertShaderID;
	uint32_t FragShaderID;

	uint32_t* begin();
	uint32_t* end();
};

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::string& VertexSource, const std::string& FragmentSource);
	~ShaderProgram();

	bool AttachShader(const std::string& Source, uint32_t ShaderType);
	void Link();
	void Bind() const;
	void Unbind() const;

	void SetUniformMat4f(const std::string& Name, const glm::mat4& matrix) const;
	void SetUniform1f(const std::string& Name, float Value) const;
	void SetUniform2f(const std::string& Name, const glm::vec2& Vec2) const;
	void SetUniform3f(const std::string& Name, const glm::vec3& Vec3) const;
	void SetUniform4f(const std::string& Name, const glm::vec4& Vec4) const;
	void SetUniform1ui(const std::string& Name, uint32_t Value) const;
	void SetUniform1i(const std::string& Name, int32_t Value) const;
	void SetUniform1iv(const std::string& Name, int Count, int* Value) const;

	int GetUniformLocation(const std::string& Name) const;

	uint32_t m_ProgramID;
private:
	ShaderIDs m_Shaders;
std::array<uint32_t, Renderer::maxUniformBufferBindings> BindingPoints;
	mutable std::unordered_map<std::string, int> m_UniformLacationCache;
};


}