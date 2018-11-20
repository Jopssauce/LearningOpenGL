#pragma once
#include "Renderer.h"

class VertexBuffer
{
private:
	unsigned int id;
public:
	//Store data in buffers to be used by shaders. Data can be things like vertices
	//Size means size in bytes
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};