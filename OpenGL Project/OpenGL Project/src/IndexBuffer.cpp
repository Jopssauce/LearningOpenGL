#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	//Store data in buffers to be used by shaders
	GLErrorCall(glGenBuffers(1, &id));
	GLErrorCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	//Initializes buffer data to store
	GLErrorCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLErrorCall(glDeleteBuffers(1, &id));
}

void IndexBuffer::Bind() const
{
	GLErrorCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::Unbind() const
{
	GLErrorCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
