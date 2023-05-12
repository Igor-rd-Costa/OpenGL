#pragma once

#include "Macros.h"
#include "glm/glm.hpp"
#include "Window.h"
#include <memory>
#include <functional>

namespace Core
{
	class PerspectiveCamera;
	class Texture;

	class CORE_API Application
	{
	public:
		virtual ~Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(Application&) = delete;


		void Run(std::function<void()> onRender);
		virtual void onRender() = 0;
		static void SetActiveCamera(PerspectiveCamera* Camera);
		
	protected:
		Application(const WindowInfo& windowInfo);
		Window* GetWindow();
		
	private:
		static PerspectiveCamera* ActiveCamera;
		std::unique_ptr<Window> m_Window;
		bool isRunning;
		friend class Renderer;


	};

	Application* CreateApplication(const WindowInfo& windowInfo);


}