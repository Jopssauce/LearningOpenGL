#include "Transform.h"



Transform::Transform()
{
	model = glm::mat4();
}


Transform::~Transform()
{
}

void Transform::Translate(glm::vec3 position)
{
	model = glm::translate(model, position);
}

void Transform::Scale(glm::vec3 scale)
{
	glm::scale(model, scale);
}

void Transform::Rotate(glm::vec3 rotate)
{
	model = glm::rotate(model, rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 Transform::GetPosition()
{
	position = glm::vec3(model[3]);
	return position;
}

glm::vec3 Transform::GetScale()
{
	scale = glm::vec3(glm::sqrt(model[0][0] * model[0][0] + model[0][1] * model[0][1] + model[0][2] * model[0][2]));
	return scale;
}

glm::vec3 Transform::GetRotation()
{
	glm::mat3 rotationMat;
	rotationMat = glm::mat3(model);
	rotation = glm::vec3(1.0f, 1.0f, 1.0f) * rotationMat;
	return rotation;
}

float * Transform::GetValue()
{
	return glm::value_ptr(model);
}
