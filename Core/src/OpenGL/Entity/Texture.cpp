#include "Texture.h"
#include <iostream>
#include "GL/glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace Core {

Texture::Texture()
{

}

Texture::Texture(const std::string& Path)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(Path.c_str(), &m_Width, &m_Height, &m_BBP, 4);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);


	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	
}

void Texture::LoadTexture(const std::string& Path)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(Path.c_str(), &m_Width, &m_Height, &m_BBP, 4);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}


void Texture::Bind(uint32_t Slot)
{
	glActiveTexture(GL_TEXTURE0 + Slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	m_TextureSlot = Slot;
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

}