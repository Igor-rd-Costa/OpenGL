#include "VertexArray.h"
#include "GL/glew.h"

namespace Core {

uint32_t AttribPointers::GetSizeOfType(uint32_t Type)
{
	switch (Type)
	{
	case GL_FLOAT: return sizeof(GLfloat);
		break;
	case GL_UNSIGNED_INT: return sizeof(GLuint);
		break;
	case GL_DOUBLE: return sizeof(GLdouble);
		break;
	//default: { throw new _exception(); }
	}
}

VertexArray::VertexArray()
	:m_AttribCount(0), m_TotalStride(0)
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArray::~VertexArray()
{
	
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}


void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetAttribPointers()
{
	uint32_t Offset = 0;
	for (const AttribPointers& AttribPointer : m_AttribPointers)
	{
		glEnableVertexArrayAttrib(m_VertexArrayID, AttribPointer.Slot);

		if (AttribPointer.Type == GL_FLOAT)
			glVertexAttribPointer(AttribPointer.Slot, AttribPointer.Count, AttribPointer.Type, AttribPointer.Normalized, m_TotalStride, (const void*)Offset);
		else if (AttribPointer.Type == GL_UNSIGNED_INT)
			glVertexAttribIPointer(AttribPointer.Slot, AttribPointer.Count, AttribPointer.Type, m_TotalStride, (const void*)Offset);
		Offset += AttribPointer.Count * AttribPointers::GetSizeOfType(AttribPointer.Type);
	}
}

template<>
void VertexArray::AddAttribPointer<float>(uint32_t Count)
{
	m_AttribPointers.push_back({ m_AttribCount, GL_FLOAT, Count, GL_FALSE });
	m_TotalStride += Count * AttribPointers::GetSizeOfType(GL_FLOAT);
	m_AttribCount++;
}

template<>
void VertexArray::AddAttribPointer<uint32_t>(uint32_t Count)
{
	m_AttribPointers.push_back({ m_AttribCount, GL_UNSIGNED_INT, Count, GL_FALSE });
	m_TotalStride += Count * AttribPointers::GetSizeOfType(GL_UNSIGNED_INT);
	m_AttribCount++;
}

template<>
void VertexArray::AddAttribPointer<double>(uint32_t Count)
{
	m_AttribPointers.push_back({ m_AttribCount, GL_DOUBLE, Count, GL_FALSE });
	m_TotalStride += Count * AttribPointers::GetSizeOfType(GL_DOUBLE);
	m_AttribCount++;
}

}