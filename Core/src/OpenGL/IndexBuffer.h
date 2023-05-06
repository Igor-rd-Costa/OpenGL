#pragma once
#include <cstdint>

namespace Core {

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(size_t Size, const void* Data);
	~IndexBuffer();

	void SetData(size_t Size, const void* Data);
	void Bind() const;
	void Unbind() const;

private:
	uint32_t m_BufferID;
};

}