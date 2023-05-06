#pragma once
#include <Windows.h>
#include <stdint.h>
#include "Macros.h"

namespace Core {

struct WindowInfo {
	HINSTANCE& hInstance;
	int& nShowCmd;
	const wchar_t* windowName;
};

class Window
{
public:
	Window(const WindowInfo& windowInfo);
	~Window();
	bool Update();
	static LARGE_INTEGER PerfCounterFrequency;
	int Width;
	int Height;
private:
	static LRESULT WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	RECT Rect;
	HWND hWnd;
	HDC hDC;
	HGLRC hGLRC;
	MSG Msg;
	friend class Application;
};


}