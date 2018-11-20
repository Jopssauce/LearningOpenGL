#pragma once
#include "Renderer.h"

class IndexBuffer
{
private:
	unsigned int id;
	//How many indices there are in the buffer
	unsigned int count;
public:
	//Store data in buffers to be used by shaders. Data can be things like indices. Indices can be used to reause vertices to avoid duplicating them
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const { return count; }

};