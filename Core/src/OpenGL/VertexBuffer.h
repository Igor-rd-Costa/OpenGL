#pragma once
#include <cstdint>

namespace Core {

class VertexBuffer
{
public:
	VertexBuffer(size_t Size);
	VertexBuffer(size_t Size, const void* Data);
	~VertexBuffer();
	void SubData(size_t Offset, size_t Size, const void* Data);
	void Bind();
	void Unbind();
private:
	uint32_t m_BufferID;
};

}