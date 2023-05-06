#include "Cube.h"
#include "../Core/Renderer.h"

namespace Core {
	Cube::Cube()
		:Entity(Mesh::CUBE_MESH)
	{
		Renderer::m_Primitives.push_back(this);
	}

	Cube::~Cube()
	{

	}

	void Cube::SetTexture(const std::string& texturePath)
	{
		
		this->m_Material.m_Diffuse = new Texture(texturePath);
	}

	void Cube::SetSpecular(const std::string& specularPath)
	{
		
		this->m_Material.m_Specular = new Texture(specularPath);
	}

	void Cube::SetShininess(float shininess)
	{
		this->m_Material.Shininess = shininess;
	}
	

}