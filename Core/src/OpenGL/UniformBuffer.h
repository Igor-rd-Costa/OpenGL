#pragma once

#include <vector>
#include <cstdint>

namespace Core {

class UniformBuffer {
public:
UniformBuffer(size_t size, uint32_t shaderId, const std::string& blockName);
~UniformBuffer();

void Bind(ShaderProgram* shader) const;

void SetData(const std::string& uniformName, T data);

private:
uint32_t m_Id;
uint32_t m_BindingPoint;
uint32_t m_BlockIndex;
static uint32_t s_BoundBuffer;
}
