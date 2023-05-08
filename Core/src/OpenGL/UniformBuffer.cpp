#include UniformBuffer.h
#include <glew.h>

namespace Core {

UniformBuffer::UniformBuffer()
{
glCreateBuffer(1, &m_Id);
gl_NamedBufferData(m_Id, size, nullptr, GL_DYNAMIC_DRAW);


}






}
