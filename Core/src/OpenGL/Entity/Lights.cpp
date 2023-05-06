#include "Lights.h"
#include "../Core/Renderer.h"
#include "../Core/PerspectiveCamera.h"

namespace Core {

	Light::Light(glm::vec3 position)
		:Entity(Mesh::CUBE_MESH, position), m_Active(true), m_Ambient({ 0.2f, 0.2f, 0.2f }),
		m_Diffuse({0.5f, 0.5f, 0.5f}), m_Specular({0.5f, 0.5f, 0.5f}), m_Color({1.0f, 1.0f, 1.0f})
	{
		Translate(position);
		this->Scale(glm::vec3(0.5f, 0.5f, 0.5f));
		Renderer::m_Lights.push_back(this);
		m_Index = Renderer::m_Lights.size() - 1;
	}

	Light::~Light()
	{

	}

	void Light::Erase()
	{
		delete Renderer::m_Lights[m_Index];
		Renderer::m_Lights.erase(Renderer::m_Lights.begin() + m_Index);
	}

	void Light::SetColor(glm::vec3 color)
	{
		this->m_Color = color;
		Renderer::LightShader->Bind();
		Renderer::LightShader->SetUniform3f("fColor", color);
	}

	void Light::SetTexture(const std::string& texturePath)
	{

		this->m_Material.m_Diffuse = new Texture(texturePath);
	}

	void Light::SetSpecular(const std::string& specularPath)
	{

		this->m_Material.m_Specular = new Texture(specularPath);
	}

	void Light::SetShininess(float shininess)
	{
		this->m_Material.Shininess = shininess;
	}


	DirectionalLight::DirectionalLight(glm::vec3 position)
		:Light(position), m_Direction({ -0.2f, -1.0f, -0.3f })
	{
		this->m_Ambient =  { 0.1f, 0.1f, 0.1f };
		this->m_Diffuse =  { 0.3f, 0.3f, 0.3f };
		this->m_Specular = { 0.2f, 0.2f, 0.2f };
	}

	DirectionalLight::~DirectionalLight() {}

	void DirectionalLight::SetUniforms()
	{
			Renderer::EntityShader->Bind();
			Renderer::EntityShader->SetUniform1i("dirLight.on", 1);
			Renderer::EntityShader->SetUniform3f("dirLight.direction", this->m_Direction);
			Renderer::EntityShader->SetUniform3f("dirLight.ambient", this->m_Ambient);
			Renderer::EntityShader->SetUniform3f("dirLight.diffuse", this->m_Diffuse);
			Renderer::EntityShader->SetUniform3f("dirLight.specular", this->m_Specular);

			Renderer::LightShader->Bind();
			Renderer::LightShader->SetUniform1i("dirLight.visible", 0);
	}

	void DirectionalLight::Toggle()
	{
		Renderer::EntityShader->Bind();
		Renderer::EntityShader->SetUniform1i("dirLight.on", (~m_Active));
	}


	PointLight::PointLight(glm::vec3 position)
		:Light(position), m_Constant(0.0f), m_Linear(0.09f), m_Quadratic(0.032f)
	{

	}

	PointLight::~PointLight() {}

	void PointLight::SetUniforms()
	{
			Renderer::EntityShader->Bind();
			Renderer::EntityShader->SetUniform1i("pointLight.on", 1);
			Renderer::EntityShader->SetUniform3f("pointLight.position", this->m_Position);
			Renderer::EntityShader->SetUniform3f("pointLight.ambient", this->m_Ambient);
			Renderer::EntityShader->SetUniform3f("pointLight.diffuse", this->m_Diffuse);
			Renderer::EntityShader->SetUniform3f("pointLight.specular", this->m_Specular);
			Renderer::EntityShader->SetUniform1f("pointLight.constant", this->m_Constant);
			Renderer::EntityShader->SetUniform1f("pointLight.linear", this->m_Constant);
			Renderer::EntityShader->SetUniform1f("pointLight.quadratic", this->m_Quadratic);

			Renderer::LightShader->Bind();
			Renderer::LightShader->SetUniform1i("pointLight.visible", 1);
	}

	void PointLight::Toggle()
	{
		Renderer::EntityShader->Bind();
		Renderer::EntityShader->SetUniform1i("pointLight.on", (~m_Active));
	}


	SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction)
		:Light(position), m_Direction(direction), m_InnerCutOff(glm::radians(17.5f)), m_OuterCutOff(glm::radians(22.0f)),
		m_Constant(0.0f), m_Linear(0.09f), m_Quadratic(0.032f)
	{
		m_Ambient = { 0.0f, 0.0f, 0.0f };
	}

	SpotLight::~SpotLight() {}

	void SpotLight::SetUniforms()
	{
		Renderer::EntityShader->Bind();
		Renderer::EntityShader->SetUniform1i("spotLight.on", 1);
		Renderer::EntityShader->SetUniform1f("spotLight.cutOff", cos(m_InnerCutOff));
		Renderer::EntityShader->SetUniform1f("spotLight.outerCutOff", cos(m_OuterCutOff));
		Renderer::EntityShader->SetUniform1f("spotLight.constant", m_Constant);
		Renderer::EntityShader->SetUniform1f("spotLight.linear", m_Linear);
		Renderer::EntityShader->SetUniform1f("spotLight.quadratic", m_Quadratic);
		Renderer::EntityShader->SetUniform3f("spotLight.ambient", m_Ambient);
		Renderer::EntityShader->SetUniform3f("spotLight.diffuse", m_Diffuse);
		Renderer::EntityShader->SetUniform3f("spotLight.specular", m_Specular);

		Renderer::LightShader->Bind();
		Renderer::LightShader->SetUniform1i("spotLight.visible", 0);
	}

	void SpotLight::Toggle()
	{
		Renderer::EntityShader->Bind();
		Renderer::EntityShader->SetUniform1i("spotLight.on", (!m_Active));
		m_Active = !m_Active;
	}

	void SpotLight::UpdatePosition(PerspectiveCamera* camera)
	{
		Renderer::EntityShader->Bind();
		Renderer::EntityShader->SetUniform3f("spotLight.position", camera->m_CameraPosition);
		Renderer::EntityShader->SetUniform3f("spotLight.direction", camera->m_CameraFront);
	}
}