#pragma once
#include <cstdint>
namespace Core {

class GLDebug
{
public:
	static void Init();
	GLDebug(GLDebug&) = delete;

	static void DebugCallback(uint32_t Source, uint32_t Type, uint32_t Id, uint32_t Severity, int32_t Length, const char* Message, const void* UserParam);
private:
	GLDebug();
};
}