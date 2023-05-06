#include "Entity.h"
#include "../Core/Renderer.h"
namespace Core {

Entity::Entity(Mesh::MeshID meshID, glm::vec3 position)
	:m_Position(position), MeshID(meshID), m_Scale({1.0f, 1.0f, 1.0f})
{
	ModelMatrix = glm::translate(glm::mat4(1.0f), position);
	
}

void Entity::Translate(glm::vec3 newPosition)
{
	this->m_Position = newPosition;
	this->ModelMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	Scale(this->m_Scale);
	
}

void Entity::Scale(glm::vec3 value)
{
	m_Scale = value;
	ModelMatrix = glm::scale(ModelMatrix, value);
}

void Entity::BindTextures() const
{
	if (this->m_Material.m_Diffuse != nullptr && this->m_Material.m_Specular != nullptr)
	{
		this->m_Material.m_Diffuse->Bind(0);
		this->m_Material.m_Specular->Bind(1);
	}
}

Entity::~Entity()
{

}

}