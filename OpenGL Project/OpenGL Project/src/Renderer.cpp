#include "Renderer.h"
#include <iostream>

using namespace std;


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	//True if no error
	while (GLenum error = glGetError())
	{
		//Prints the error, the function string the error came from, the file its called in, and the line number
		cout << "[OpenGL ERROR] " << error << ": " << function << " " << file << ":" << line << endl;
		return false;
	}
	return true;
}

void Renderer::Draw(IndexBuffer & ib, VertexArray & va, Shader & shader, GLenum mode, GLsizei count, GLenum type, const void * indices)
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	GLErrorCall(glDrawElements(mode, count, type, indices));
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
