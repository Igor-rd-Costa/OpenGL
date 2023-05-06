#pragma once

#include <Windows.h>
#include "Window.h"

extern Core::Application* Core::CreateApplication(const WindowInfo& windowInfo);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	auto App = Core::CreateApplication({ hInstance, nShowCmd, L"Hello" });
	App->Run([&App]() {App->onRender(); });
	FreeConsole();
	delete App;
}