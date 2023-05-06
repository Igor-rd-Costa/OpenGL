#pragma once
#include <array>

#include "glm/glm.hpp"

#include "Texture.h"

namespace Core {

struct Material
{
	Texture* m_Diffuse = nullptr;
	Texture* m_Specular = nullptr;
	float Shininess = 0.25f;
	unsigned int m_Alpha = 1;
};

}
