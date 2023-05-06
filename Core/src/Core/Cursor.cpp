#include "Cursor.h"

namespace Core {

	float Cursor::posX, Cursor::posY, Cursor::lastPosX, Cursor::lastPosY, Cursor::offSetX, Cursor::offSetY;
	bool Cursor::clipOn;
	bool Cursor::centered;
	bool Cursor::m_RightButtonDown;
	bool Cursor::m_RightButtonClick;
	bool Cursor::m_leftButton;
	
	void Cursor::Center(const RECT& windowRect)
	{
		Cursor::lastPosX = ((float)windowRect.left + (float)windowRect.right)  / 2.0f;
		Cursor::lastPosY = ((float)windowRect.top  + (float)windowRect.bottom) / 2.0f;
		SetCursorPos((int)Cursor::lastPosX, (int)Cursor::lastPosY);
	}

	void Cursor::Update(const RECT& windowRect)
	{
		static POINT CursorPos;
		GetCursorPos(&CursorPos);
		Cursor::posX = (float)CursorPos.x;
		Cursor::posY = (float)CursorPos.y;

		Cursor::offSetX = Cursor::posX - Cursor::lastPosX;
		Cursor::offSetY = Cursor::posY - Cursor::lastPosY;

		Cursor::lastPosX = Cursor::posX;
		Cursor::lastPosY = Cursor::posY;

		if (Cursor::clipOn)
		{
			if ((Cursor::posX - 1 <= windowRect.left || Cursor::posX - 1 <= 0)
				|| (Cursor::posX + 1 >= windowRect.right || Cursor::posX + 1 >= 2000) // Get Screen Width
				|| (Cursor::posY - 1 <= windowRect.top || Cursor::posY - 1 <= 0)
				|| (Cursor::posY + 1 >= windowRect.bottom || Cursor::posY + 1 >= 2000)) // Get Screen Height
			{
				Cursor::Center(windowRect);
				Cursor::centered = true;
			}
			else
			{
				Cursor::centered = false;
			}
		}
	}

	bool Cursor::RightButtonClick()
	{
		bool awnser = m_RightButtonClick;
		if(awnser)
			m_RightButtonClick = !m_RightButtonClick;
		return awnser;
	}

	void Cursor::Clip(RECT* windowRect)
	{
		if (!Cursor::clipOn) {
			Cursor::clipOn = true;
			ClipCursor(windowRect);
			ShowCursor(false);
			Cursor::Center(*windowRect);
		}
		else {
			ClipCursor(NULL);
			ShowCursor(true);
			Cursor::clipOn = false;
		}
	}
}