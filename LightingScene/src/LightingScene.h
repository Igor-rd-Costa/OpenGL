#pragma once

#include "Core.h"


class LightingScene : public Core::Application
{
public:
	LightingScene(const Core::WindowInfo& windowInfo);
	~LightingScene();
	void onRender() override;
	void Render();
private:
	Core::PerspectiveCamera* Camera;
	Core::DirectionalLight* dirLight;
	Core::PointLight* pointLight;
	Core::SpotLight* spotLight;

};

Core::Application* Core::CreateApplication(const WindowInfo& windowInfo)
{
	return new LightingScene(windowInfo);
}