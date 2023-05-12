#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace Core {

class UniformBuffer {
	public:
	UniformBuffer(size_t size, uint32_t shaderId, const std::string& blockName);
	~UniformBuffer();
	
	void Bind(uint32_t index) const;
	void Link(uint32_t programId, const std::string& uniformBlock) const;
	
	template<typename T>
	void SetData(const std::string& uniform, T data);
	
	private:
	uint32_t m_Id;
	uint32_t m_BindingPoint;
	std::unordered_map<std::string, uint32_t> m_UniformCache;
	static uint32_t s_MaxUniformBufferBindings;
	static uint32_t s_BoundBuffers;
}
