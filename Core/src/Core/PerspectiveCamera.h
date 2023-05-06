#pragma once

#include "Macros.h"
#include "glm/glm.hpp"

namespace Core {
class Timer;

class CORE_API PerspectiveCamera
{
public:
	PerspectiveCamera(glm::vec3 CameraPosition, float CameraSpeed, float Sensitivity);
	~PerspectiveCamera();


	void Update();

	glm::mat4 m_ViewMatrix;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraFront;

	float Sensitivity;
private:
	uint32_t CamID;
	Timer* m_Timer;
	float m_CurrentFrame;
	float m_LastFrame;
	float m_DeltaTime;

	float m_Yaw;
	float m_Pitch;
	float m_CameraSpeedConst;
	float m_CameraSpeed;


	glm::vec3 m_CameraDirection;
	glm::vec3 m_WorldViewUp;

};

}