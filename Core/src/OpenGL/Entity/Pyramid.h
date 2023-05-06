#pragma once
#include "Entity.h"

namespace Core {

class CORE_API Pyramid : public Entity
{
public:
	Pyramid();
	~Pyramid();
	void SetTexture(const std::string& texturePath) override;
	void SetSpecular(const std::string& specularPath) override;
	void SetShininess(float shininess) override;
};

}