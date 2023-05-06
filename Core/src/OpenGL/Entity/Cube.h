#pragma once
#include "../Core/Macros.h"
#include "Entity.h"

namespace Core {

class CORE_API Cube : public Entity
{
public:
	Cube();
	~Cube();

	void SetTexture(const std::string& texturePath) override;
	void SetSpecular(const std::string& specularPath) override;
	void SetShininess(float shininess) override;
};

}