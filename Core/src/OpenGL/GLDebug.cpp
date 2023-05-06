#include "GLDebug.h"
#include <iostream>
#include "GL/glew.h"

namespace Core {

void GLDebug::DebugCallback(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam)
{
	std::cout << Message << std::endl;
}



void GLDebug::Init()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLDebug::DebugCallback, nullptr);
}

}
