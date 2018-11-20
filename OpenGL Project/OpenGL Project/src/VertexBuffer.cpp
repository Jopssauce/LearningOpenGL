#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	//Store data in buffers to be used by shaders
	GLErrorCall(glGenBuffers(1, &id));
	GLErrorCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	//Initializes buffer data to store
	GLErrorCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLErrorCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::Bind() const
{
	GLErrorCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Unbind() const
{
	GLErrorCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
