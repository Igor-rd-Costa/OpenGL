#pragma once
#include <cstdint>
#include <string>
#include "../Core/Macros.h"
namespace Core {

class CORE_API Texture
{
public:
	Texture();
	Texture(const std::string& Path);
	~Texture();

	void Bind(uint32_t Slot = 0);
	void Unbind();

	void LoadTexture(const std::string& Path);
	uint32_t m_TextureSlot;
private:
	uint32_t m_TextureID;
	unsigned char* m_LocalBuffer;
	int m_Width;
	int m_Height;
	int m_BBP;
};

}