#pragma once
#include <Windows.h>
#include <string>
#include "Macros.h"
namespace Core {

class CORE_API Timer
{
public:
	Timer(const std::string& TimerName = "");
	~Timer();

	float GetTime();
	float GetRunTime();
	void Pause();
	void Resume();
private:
	std::string m_TimerName;
	LARGE_INTEGER m_Start;
	LARGE_INTEGER m_End;
	LARGE_INTEGER m_Pause;
	LARGE_INTEGER m_Resume;
	float TotalTime;
	float PausedTime;
};
}