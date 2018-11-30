#include "VertexArray.h"

VertexArray::VertexArray(int amount)
{
	GLErrorCall(glGenVertexArrays(amount, &id));
	GLErrorCall(glBindVertexArray(id));
}

VertexArray::~VertexArray()
{
	GLErrorCall(glBindVertexArray(0));
}

void VertexArray::Bind()
{
	GLErrorCall(glBindVertexArray(id));
}

void VertexArray::Unbind()
{
	GLErrorCall(glBindVertexArray(0));
}
