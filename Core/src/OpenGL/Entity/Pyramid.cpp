#include "Pyramid.h"
#include "../Core/Renderer.h"
namespace Core {

	Pyramid::Pyramid()
		:Entity(Mesh::PYRAMID_MESH)
	{
		Renderer::m_Primitives.push_back(this);
	}

	Pyramid::~Pyramid()
	{

	}

	void Pyramid::SetTexture(const std::string& texturePath)
	{

		this->m_Material.m_Diffuse = new Texture(texturePath);
	}

	void Pyramid::SetSpecular(const std::string& specularPath)
	{

		this->m_Material.m_Specular = new Texture(specularPath);
	}

	void Pyramid::SetShininess(float shininess)
	{
		this->m_Material.Shininess = shininess;
	}
}