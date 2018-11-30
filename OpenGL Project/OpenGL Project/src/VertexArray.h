#pragma once
#include "GL/glew.h"
#include "Renderer.h"

class VertexArray
{
public:
	VertexArray(int amount);
	~VertexArray();
	void Bind();
	void Unbind();
	unsigned int id;

private:

};


