#include UniformBuffer.h
#include <glew.h>

namespace Core {
	uint32_t UniformBuffer::s_MaxUniformBufferBindings;
	uint32_t UniformBuffer::s_BoundBuffers;

	UniformBuffer::UniformBuffer(void* dataStruct)
	{
		glCreateBuffer(1, &m_Id);
		gl_NamedBufferData(m_Id, size, dataStruct, GL_DYNAMIC_DRAW);
	}
    
	void UniformBuffer::Bind(uint32_t index)
	{
		if(s_BoundBuffers < s_MaxUniformBufferBindings) {
			glBindBufferBase(GL_UNIFORM_BUFFER, index, m_Id); 
			s_BoundBuffers++;
		}
	}
	
	
    template<>
    void UniformBuffer::SetData<glm::vec3>(glm::vec3 data)
	{
		
		
		
	}





}
