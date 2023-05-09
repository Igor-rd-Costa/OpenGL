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
    void UniformBuffer::SetData<glm::vec3>(const std::string& uniform, glm::vec3 data)
	{

		
		
	}





}
