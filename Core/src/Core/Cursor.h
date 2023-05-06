#pragma once

#include <Windows.h>
#include "Macros.h"
namespace Core {

	class CORE_API Cursor
	{
	public:
		Cursor(Cursor&) = delete;

		static void Center(const RECT& windowRect);
		static void Update(const RECT& windowRect);
		static bool RightButtonClick();
		static void Clip(RECT* windowRect = nullptr);

		static float posX;
		static float posY;
		static float lastPosX;
		static float lastPosY;
		static float offSetX;
		static float offSetY;
		static bool clipOn;
		static bool centered;
	private:
		Cursor();
		static bool m_RightButtonDown;
		static bool m_RightButtonClick;
		static bool m_leftButton;
		friend class Window;
	};
}