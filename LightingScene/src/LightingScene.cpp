#include "LightingScene.h"


LightingScene::LightingScene(const Core::WindowInfo& windowInfo)
	:Application(windowInfo)
{
	using namespace Core;
	Camera = new PerspectiveCamera({ 1.0f, 1.0f, 4.0f }, 4.0f, 0.1f);
	pointLight = new PointLight();
	pointLight->Translate({ 1.0f, 3.0f, 0.0f });
	
	dirLight = new DirectionalLight();
	dirLight->Translate({ 2.0f, 0.0f, 1.0f });
	
	spotLight = new SpotLight();
	spotLight->Translate({ 1.0f, 0.0f, 0.0f });
#ifdef _DEBUG
	pointLight->SetTexture("src/Textures/DefaultTexture.png");
	pointLight->SetSpecular("src/Textures/DefaultSpecular.png");
	ContainerTex = new Texture("src/Textures/container2.png");
	ContainerSpec = new Texture("src/Textures/container2_specular.png");
#endif
#ifdef NDEBUG
	pointLight->SetTexture("Textures/DefaultTexture.png");
	pointLight->SetSpecular("Textures/DefaultSpecular.png");
	ContainerTex = new Texture("Textures/container2.png");
	ContainerSpec = new Texture("Textures/container2_specular.png");
#endif
	
	pointLight->SetUniforms();
	dirLight->SetUniforms();
	spotLight->SetUniforms();

	dirLight->m_Material.m_Alpha = 0;
	spotLight->m_Material.m_Alpha = 0;

	for (float x = -5.0f; x <= 5.0f; x = x + 1.0f)
	{
		for (float z = -5.0f; z <= 5.0f; z = z + 1.0f)
		{
			Cube* cube = new Cube();
			cube->m_Material.m_Diffuse = ContainerTex;
			cube->m_Material.m_Specular = ContainerSpec;
			cube->Translate({ x, 0.0f, z });
		}
	}

	

}

LightingScene::~LightingScene()
{
	delete Camera;
}

void LightingScene::onRender()
{
	spotLight->UpdatePosition(Camera);
	if (Core::Cursor::RightButtonClick()) spotLight->Toggle();
}
