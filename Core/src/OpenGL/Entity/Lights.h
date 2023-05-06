#pragma once
#include "Entity.h"

namespace Core
{
	class ShaderProgram;
	class PerspectiveCamera;

	class CORE_API Light : public Entity
	{
	public:
		bool m_Active;
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
		glm::vec3 m_Color;

	public:
		void SetTexture(const std::string& texturePath);
		void SetSpecular(const std::string& specularPath);
		void SetShininess(float shininess);
		void SetColor(glm::vec3 color);
		void Erase();
		virtual void Toggle() = 0;
		virtual void SetUniforms() = 0;
		virtual ~Light();
	protected:
		uint32_t m_Index;
		Light(glm::vec3 position = {0.0f, 0.0f, 0.0f});
	};


	class CORE_API DirectionalLight : public Light
	{
	public:
		glm::vec3 m_Direction;
		
	public:
		DirectionalLight(glm::vec3 position = { 0.0f, 0.0f, 0.0f });
		void SetUniforms() override;
		void Toggle() override;
		~DirectionalLight();


	};


	class CORE_API PointLight : public Light
	{
	public:
		float m_Constant;
		float m_Linear;
		float m_Quadratic;

	public:
		PointLight(glm::vec3 position = { 0.0f, 0.0f, 0.0f });
		void SetUniforms() override;
		void Toggle() override;
		~PointLight();
	};


	class CORE_API SpotLight : public Light
	{
	public:
		glm::vec3 m_Direction;
		float m_InnerCutOff;
		float m_OuterCutOff;
		float m_Constant;
		float m_Linear;
		float m_Quadratic;

	public:
		SpotLight(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 direction = {0.0f, -1.0f, 0.0f});
		void UpdatePosition(PerspectiveCamera* camera);
		void SetUniforms() override;
		void Toggle() override;
		~SpotLight();
	};

}