#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


const float YAW = -90.0f;
const float FOV = 45.0f;


class Camera
{
public:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	float m_pitch;
	float m_yaw;

	float m_fov;
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = 0, float fov = FOV);
	~Camera();
	void LookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	float * GetValue();

private:
	glm::mat4 view;
	void Recalculate();
};

