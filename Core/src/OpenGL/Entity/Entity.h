#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "../Core/Macros.h"
namespace Core {

class CORE_API Entity
{
public:
	
	void BindTextures() const;
	
	void Translate(glm::vec3 newPosition);
	void Scale(glm::vec3 value);
	virtual void SetTexture(const std::string& texturePath) = 0;
	virtual void SetSpecular(const std::string& specularPath) = 0;
	virtual void SetShininess(float shininess) = 0;
	glm::mat4 ModelMatrix;
	glm::vec3 m_Position;
	Material m_Material;
	
protected:
	glm::vec3 m_Scale;
	Entity(Mesh::MeshID meshID, glm::vec3 position = {0.0f, 0.0f, 0.0f});
	virtual ~Entity();
private:
	Mesh::MeshID MeshID;
	friend class Renderer;
};

}