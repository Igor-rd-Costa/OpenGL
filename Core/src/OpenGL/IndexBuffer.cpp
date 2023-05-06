#include "IndexBuffer.h"
#include "GL/glew.h"

namespace Core {

IndexBuffer::IndexBuffer()
{
	glCreateBuffers(1, &m_BufferID);
}

IndexBuffer::IndexBuffer(size_t Size, const void* Data)
{
	glCreateBuffers(1, &m_BufferID);
	glNamedBufferStorage(m_BufferID, Size, Data, 0);
}

IndexBuffer::~IndexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_BufferID);
}

void IndexBuffer::SetData(size_t Size, const void* Data)
{
	 
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}