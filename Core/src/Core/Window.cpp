#include "Window.h"
#include <iostream>

#include <GL/glew.h>
#include <GL/wglew.h>
#include "../OpenGL/GLDebug.h"

#include "Cursor.h"

namespace Core {

	LARGE_INTEGER Window::PerfCounterFrequency;

	Window::Window(const WindowInfo& windowInfo)
	{
		WNDCLASS wndClass = {};
		
		wndClass.lpfnWndProc = Window::WinProc;
		wndClass.lpszClassName = L"Window";
		wndClass.hInstance = windowInfo.hInstance;

		RegisterClass(&wndClass);

		this->hWnd = CreateWindowEx(
			CS_OWNDC,
			L"Window",
			windowInfo.windowName,
			WS_BORDER | WS_SYSMENU,
			100,
			50,
			1400,
			800,
			NULL,
			NULL,
			windowInfo.hInstance,
			NULL);

		this->hDC = GetDC(this->hWnd);

		SetWindowLongPtr(this->hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		PIXELFORMATDESCRIPTOR PFD = {
		sizeof(PFD),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		LPD_TYPE_RGBA,
		32,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0,
		0,
		0
		};

		int format = ChoosePixelFormat(this->hDC, &PFD);

		if (!format)
		{
			std::cout << "Could not find a valid PixelFormat!" << std::endl;
		}
		else
		{
			SetPixelFormat(this->hDC, format, &PFD);
		}

		HGLRC dummy = wglCreateContext(this->hDC);
		wglMakeCurrent(this->hDC, dummy);

		GLenum error = glewInit();

		if (error != GLEW_OK)
		{
			std::cout << "Failed to Initialize GLEW!" << std::endl;
		}
		else
		{
			int attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 6,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0
			};


			this->hGLRC = wglCreateContextAttribsARB(this->hDC, this->hGLRC, attribs);


			wglMakeCurrent(0, 0);

			wglDeleteContext(dummy);

			wglMakeCurrent(this->hDC, this->hGLRC);

#ifdef _DEBUG
			GLDebug::Init();
#endif
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			ShowWindow(this->hWnd, windowInfo.nShowCmd);
			QueryPerformanceFrequency(&PerfCounterFrequency);
		}
	}

	Window::~Window()
	{

	}

	LRESULT Window::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (uMsg)
		{
		case WM_RBUTTONDOWN: {
				Cursor::m_RightButtonClick = true;
		} break;
		case WM_RBUTTONUP: {
			Cursor::m_RightButtonClick = false;
		} break;
		case WM_KEYDOWN: {
			if (wParam == 27) Cursor::Clip(&window->Rect); //ESC
			//std::cout << wParam << "\n";

		} break;
		case WM_SIZE: {
			GetWindowRect(window->hWnd, &window->Rect);
			window->Width = LOWORD(lParam);
			window->Height = HIWORD(lParam);
		} break;
		case WM_MOVE: {
			GetWindowRect(window->hWnd, &window->Rect);
		} break;
		case WM_EXITSIZEMOVE: {
			GetWindowRect(window->hWnd, &window->Rect);
		} break;
		case WM_DESTROY: {
			PostQuitMessage(0);
		} break;
		default: {
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		} break;
		}
		return 0;
	}

	bool Window::Update()	
	{

		while (PeekMessage(&this->Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (this->Msg.message == WM_QUIT) {
				return false;
			}

			TranslateMessage(&this->Msg);
			DispatchMessage(&this->Msg);
			return true;
		}
		return true;
	}
}