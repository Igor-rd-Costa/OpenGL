#include "Timer.h"
#include "Window.h"

#include <iostream>

namespace Core {

Timer::Timer(const std::string& TimerName)
	:m_TimerName(TimerName), PausedTime(0.0f), TotalTime(0.0f)
{
	QueryPerformanceCounter(&m_Start);
	QueryPerformanceCounter(&m_Pause);
	QueryPerformanceCounter(&m_Resume);
	QueryPerformanceCounter(&m_End);
}

Timer::~Timer()
{
	if (m_TimerName != "")
	{
		std::cout << "[" << m_TimerName << " Timer] Ended after " << GetTime() << " seconds." << std::endl;
	}
}

float Timer::GetTime()
{
	QueryPerformanceCounter(&m_End);
	TotalTime = (m_End.QuadPart - m_Start.QuadPart) / (float)Window::PerfCounterFrequency.QuadPart;
	return TotalTime - PausedTime;
}

float Timer::GetRunTime()
{
	QueryPerformanceCounter(&m_End);
	return (m_End.QuadPart - m_Start.QuadPart) / (float)Window::PerfCounterFrequency.QuadPart;
}


void Timer::Pause()
{
	QueryPerformanceCounter(&m_Pause);
}

void Timer::Resume()
{
	QueryPerformanceCounter(&m_Resume);
	PausedTime += ((m_Resume.QuadPart - m_Pause.QuadPart) / (float)Window::PerfCounterFrequency.QuadPart);
}

}