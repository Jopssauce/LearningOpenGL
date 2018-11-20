#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	//Store data in buffers to be used by shaders
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	//Initializes buffer data to store
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
