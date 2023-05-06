#include "PerspectiveCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Cursor.h"
#include "Application.h"
#include "Timer.h"
#include <iostream>
namespace Core {

PerspectiveCamera::PerspectiveCamera(glm::vec3 CameraPosition, float CameraSpeed, float Sensitivity)
	:m_ViewMatrix(glm::mat4(1.0f)), m_CameraPosition(CameraPosition), m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_WorldViewUp(glm::vec3(0.0f, 1.0f, 0.0f)), 
	m_CameraDirection(glm::vec3(0.0f, 0.0f, 0.0f)), m_CameraSpeedConst(CameraSpeed), m_CameraSpeed(0.0f), m_Yaw(-90.0f), m_Pitch(0.0f), 
	m_CurrentFrame(0.0f), m_LastFrame(0.0f), m_DeltaTime(0.0f), Sensitivity(Sensitivity)
{
	m_Timer = new Timer();
	Application::SetActiveCamera(this);
}

PerspectiveCamera::~PerspectiveCamera()
{
	delete m_Timer;
}

void PerspectiveCamera::Update()
{
	m_CurrentFrame = m_Timer->GetTime();
	m_DeltaTime = m_CurrentFrame - m_LastFrame;
	m_LastFrame = m_CurrentFrame;
	
	m_CameraSpeed = m_CameraSpeedConst * m_DeltaTime;

	if (Cursor::clipOn)
	{
		if (Cursor::centered)
		{
			Cursor::offSetX = 0.0f;
			Cursor::offSetY = 0.0f;
		}

		m_Yaw += Cursor::offSetX * Sensitivity;
		m_Pitch += -Cursor::offSetY * Sensitivity;

		if (m_Pitch > 89.0f) m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		m_CameraDirection.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraDirection.y = sin(glm::radians(m_Pitch));
		m_CameraDirection.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront = glm::normalize(m_CameraDirection);

		if (GetAsyncKeyState('W'))
			m_CameraPosition += m_CameraFront * m_CameraSpeed;
		if (GetAsyncKeyState('S'))
			m_CameraPosition -= m_CameraFront * m_CameraSpeed;
		if (GetAsyncKeyState('A'))
			m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_WorldViewUp)) * m_CameraSpeed;
		if (GetAsyncKeyState('D'))
			m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_WorldViewUp)) * m_CameraSpeed;
		if (GetAsyncKeyState(32)) // Space Bar
			m_CameraPosition.y += m_CameraSpeed;
		if (GetAsyncKeyState(16)) // LShift
			m_CameraPosition.y -= m_CameraSpeed;
	}
	
	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_WorldViewUp);

}
}