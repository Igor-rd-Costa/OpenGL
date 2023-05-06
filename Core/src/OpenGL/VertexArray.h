#pragma once

#include <cstdint>
#include <vector>

namespace Core {

struct AttribPointers
{
	uint32_t Slot;
	uint32_t Type;
	uint32_t Count;
	unsigned char Normalized;

	static uint32_t GetSizeOfType(uint32_t Type);
};


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void SetAttribPointers();
	template <typename T>
	void AddAttribPointer(uint32_t Count);

private:
	std::vector<AttribPointers> m_AttribPointers;
	uint32_t m_VertexArrayID;
	uint32_t m_AttribCount;
	uint32_t m_TotalStride;

};

}
