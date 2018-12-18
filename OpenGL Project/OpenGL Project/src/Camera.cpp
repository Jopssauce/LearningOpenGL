#include "Camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float fov)
{
	cameraPos = pos;
	cameraFront = front;
	cameraUp = up;
	m_pitch = pitch;
	m_yaw = yaw;
	m_fov = fov;
	LookAt(pos, front, up);
	Recalculate();
}

Camera::~Camera()
{
}

void Camera::LookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
	view = glm::lookAt(pos, target, up);
	Recalculate();
}

float * Camera::GetValue()
{
	return glm::value_ptr(view);
}

void Camera::Recalculate()
{
	if (m_pitch > 89.0f) m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_yaw));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	cameraFront = glm::normalize(front);
}
