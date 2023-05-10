#include UniformBuffer.h
#include <glew.h>

namespace Core {
	uint32_t UniformBuffer::s_MaxUniformBufferBindings;
	uint32_t UniformBuffer::s_BoundBuffers;

	UniformBuffer::UniformBuffer(void* dataStruct)
	{
		glCreateBuffer(1, &m_Id);
		glNamedBufferStorage(m_Id, size, dataStruct, GL_DYNAMIC_STORAGE_BIT);
	}
    
	void UniformBuffer::Bind(uint32_t index) const
	{
		if(s_BoundBuffers < s_MaxUniformBufferBindings) {
			glBindBufferBase(GL_UNIFORM_BUFFER, index, m_Id); 
			s_BoundBuffers++;
			m_BindingPoint = index;
		}
	}
	

	void UniformBuffer::Link(uint32_t programId, const std::string& uniformBlock) const
	{
		uint32_t blockIndex = glGetUniformBlockIndex(shaderId, uniform);
		glUniformBlockBinding(programId, blockIndex, m_BindingPoint);
	}
	
	template<>
	void UniformBuffer::SetData<glm::vec3>(uint32_t programId, const std::string& uniform, glm::vec3 data)
	{
		uint32_t offset;
		uint32_t index = m_UniformCache.find(uniform);
		if(index == m_UniformCache.end()) {
			index = glGetUniformLocation(programId, uniform);
			m_UniformCache.insert({uniform, index});
		}
		glGetActiveUniformsiv(programId, 1, index, GL_UNIFORM_OFFSET, &offset);
		glNamedBufferSubData(m_Id, offset, sizeof(glm::vec3), &data);
	}





}
