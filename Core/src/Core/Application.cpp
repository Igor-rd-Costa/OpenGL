#include "Application.h"
#include <Windows.h>
#include <iostream>
#include "Renderer.h"
#include "Window.h"
#include "Cursor.h"
#include "../OpenGL/Entity/Cube.h"
#include "../OpenGL/Entity/Pyramid.h"
#include "PerspectiveCamera.h"
#include "GL/glew.h"
#include <GL/GL.h>
#include <fstream>

namespace Core
{
	PerspectiveCamera* Application::ActiveCamera;
	Application::Application(const WindowInfo& windowInfo)
		:isRunning(true)
	{

#ifdef _DEBUG
		AllocConsole();
		FILE* consoleStream;
		freopen_s(&consoleStream, "CONOUT$", "w", stdout);
#endif

		m_Window = std::make_unique<Window>(windowInfo);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		Cursor::Clip(&m_Window->Rect);
		Renderer::Init(m_Window.get());
	
	}


	Application::~Application()
	{
		Renderer::Shutdown();
		delete ContainerTex;
		delete ContainerSpec;
	}

	void Application::Run(std::function<void()> onRender)
	{
		while (this->isRunning) {

			if (!this->m_Window->Update()) {
				this->isRunning = false;
				break;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Cursor::Update(m_Window->Rect);
			onRender();
			
			Renderer::Draw(Application::ActiveCamera);

			SwapBuffers(m_Window->hDC);
		}
	}

	void Application::SetActiveCamera(PerspectiveCamera* Camera)
	{
		ActiveCamera = Camera;
	}

	Window* Application::GetWindow()
	{
		return m_Window.get();
	}
}
