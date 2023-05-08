#pragma once
#include "../OpenGL/Entity/Texture.h"
#include "../OpenGL/Entity/Entity.h"
#include "../OpenGL/Entity/Lights.h"
#include "../OpenGL/ShaderProgram.h"
#include <memory>
namespace Core {
class Window;
class PerspectiveCamera;

class Renderer
{
public:
	static void Init(Window* mainWindow);
	static void Shutdown();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;

	static void Draw(PerspectiveCamera* Camera);
	static Mesh* GetMeshData(Mesh::MeshID ID);
	static std::vector<Entity*> m_Primitives;
	static std::vector<Light*> m_Lights;
	static std::unique_ptr<ShaderProgram> EntityShader;
	static std::unique_ptr<ShaderProgram> LightShader;

protected:
private:
        static int maxUniformBufferBindings;
	static glm::mat4 ProjMatrix;
	static Mesh* CubeMesh;
	static Mesh* PyramidMesh;



	static void Render();
	Renderer();
	~Renderer() = delete;
};

}

