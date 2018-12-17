#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Transform
{
public:
	
	Transform();
	~Transform();

	void Translate(glm::vec3 position);
	void Scale(glm::vec3 scale);
	void Rotate(glm::vec3 rotate);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	float * GetValue();
private:
	glm::mat4 model;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

