#include "VertexBuffer.h"
#include "GL/glew.h"

namespace Core {

VertexBuffer::VertexBuffer(size_t Size)
{
	static const int flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT;
	glCreateBuffers(1, &m_BufferID);
	glNamedBufferStorage(m_BufferID, Size, NULL, flags);
}

VertexBuffer::VertexBuffer(size_t Size, const void* Data)
{
	static const int flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT;
	glCreateBuffers(1, &m_BufferID);
	glNamedBufferStorage(m_BufferID, Size, Data, flags);
}

VertexBuffer::~VertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_BufferID);
}

void VertexBuffer::SubData(size_t Offset, size_t Size, const void* Data)
{
	glNamedBufferSubData(m_BufferID, Offset, Size, Data);
}


void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}