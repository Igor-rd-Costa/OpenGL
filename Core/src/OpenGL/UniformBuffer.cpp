#include UniformBuffer.h
#include <glew.h>

namespace Core {

UniformBuffer::UniformBuffer(void* dataStruct)
{
glCreateBuffer(1, &m_Id);
 gl_NamedBufferData(m_Id, size, dataStruct, GL_DYNAMIC_DRAW);
}





}
