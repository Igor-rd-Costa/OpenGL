#include "Renderer.h"

#include "GL/glew.h"
#include <iostream>
#include "Window.h"
#include "PerspectiveCamera.h"
namespace Core {

	Mesh* Renderer::CubeMesh;
	Mesh* Renderer::PyramidMesh;
	std::vector<Entity*> Renderer::m_Primitives;
	std::vector<Light*> Renderer::m_Lights;
	std::unique_ptr<ShaderProgram> Renderer::EntityShader;
	std::unique_ptr<ShaderProgram> Renderer::LightShader;
	glm::mat4 Renderer::ProjMatrix;
 int Renderer::maxUniformBufferBindings;

	void Renderer::Init(Window* mainWindow)
	{
		CubeMesh = new Mesh(Mesh::CUBE_MESH);
		PyramidMesh = new Mesh(Mesh::PYRAMID_MESH);
		ProjMatrix = glm::perspective(glm::radians(70.0f), (float)mainWindow->Width / (float)mainWindow->Height, 0.1f, 100.0f);

		EntityShader = std::make_unique<ShaderProgram>("../Core/src/OpenGL/Shaders/MultipleLightsVertex.glsl", "../Core/src/OpenGL/Shaders/MultipleLightsFragment.glsl");
		LightShader = std::make_unique<ShaderProgram>("../Core/src/OpenGL/Shaders/LightSourceVertex.glsl", "../Core/src/OpenGL/Shaders/LightSourceFragment.glsl");

  glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &Renderer::maxUniformBufferBindings);
		
EntityShader->Bind();
		EntityShader->SetUniform1i("material.diffuse", 0);
		EntityShader->SetUniform1i("material.specular", 1);
		EntityShader->SetUniformMat4f("ProjMatrix", ProjMatrix);

		LightShader->Bind();
		LightShader->SetUniformMat4f("ProjMatrix", ProjMatrix);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void Renderer::Shutdown()
	{
		if (!m_Primitives.empty()) {
			for (Entity* entity : m_Primitives) {
				delete entity;
			}
			m_Primitives.clear();
		}

		if (!m_Lights.empty()) {
			for (Light* light : m_Lights) {
				delete light;
			}
		}

		delete CubeMesh;
		delete PyramidMesh;
	}

	void Renderer::Draw(PerspectiveCamera* Camera)
	{
		EntityShader->Bind();
		Camera->Update();
		EntityShader->SetUniformMat4f("ViewMatrix", Camera->m_ViewMatrix);
		EntityShader->SetUniform3f("ViewPos", Camera->m_CameraPosition);
		for (Entity* entity : m_Primitives) {
			Mesh* mesh = Renderer::GetMeshData(entity->MeshID);
			if (mesh == nullptr) {
				std::cout << "[Renderer Error] Entity was not heap allocated.\n";
				return;
			}
			mesh->m_VertexArray->Bind();
			mesh->m_IndexBuffer->Bind();
			EntityShader->SetUniform1f("material.shininess", entity->m_Material.Shininess);
			EntityShader->SetUniform1i("material.alpha", entity->m_Material.m_Alpha);
			EntityShader->SetUniformMat4f("ModelMatrix", entity->ModelMatrix);
			entity->BindTextures();
			glDrawElements(GL_TRIANGLES, mesh->IndexSize, GL_UNSIGNED_INT, 0);

		}

		LightShader->Bind();
		LightShader->SetUniformMat4f("ViewMatrix", Camera->m_ViewMatrix);
		for (Light* light : m_Lights) {
			Mesh* mesh = Renderer::GetMeshData(light->MeshID);
			if (mesh == nullptr) {
				std::cout << "[Renderer Error] Light source was not heap allocated.\n";
				return;
			}
			mesh->m_VertexArray->Bind();
			mesh->m_IndexBuffer->Bind();
			LightShader->SetUniform1f("material.shininess", light->m_Material.Shininess);
			LightShader->SetUniform1i("material.alpha", light->m_Material.m_Alpha);
			LightShader->SetUniformMat4f("ModelMatrix", light->ModelMatrix);
			light->BindTextures();
			glDrawElements(GL_TRIANGLES, mesh->IndexSize, GL_UNSIGNED_INT, 0);
		}

	}

	Mesh* Renderer::GetMeshData(Mesh::MeshID ID)
	{
		switch (ID)
		{
		case Mesh::CUBE_MESH: return CubeMesh;
			break;
		case Mesh::PYRAMID_MESH: return PyramidMesh;
			break;
		default: return nullptr;
			break;
		}
	}

	void Renderer::Render()
	{
		
	}

}