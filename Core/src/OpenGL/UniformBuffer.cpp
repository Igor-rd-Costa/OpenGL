#include UniformBuffer.h
#include <glew.h>

namespace Core {

	UniformBuffer::UniformBuffer(void* dataStruct)
	{
		glCreateBuffer(1, &m_Id);
		gl_NamedBufferData(m_Id, size, dataStruct, GL_DYNAMIC_DRAW);
	}
    
	void UniformBuffer::Bind(uint32_t index)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, m_Id);
	}
	
	
    template<>
    void UniformBuffer::SetData<glm::vec3>(glm::vec3 data)
	{
		
		
		
	}





}
