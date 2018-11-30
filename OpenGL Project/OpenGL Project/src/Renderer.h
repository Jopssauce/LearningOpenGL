#pragma once
#include "GL/glew.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
class IndexBuffer;
class VertexArray;
class Shader;
//MACROS
//Break if false
#define ASSERT(x) if (!(x)) __debugbreak();
//Calls Clear then the function to check for errors then GLLogCall
#define GLErrorCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//NOTE: Improve this soon using OpenGL Debug Output
void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Draw(IndexBuffer &ib, VertexArray &va, Shader &shader, GLenum mode, GLsizei count, GLenum type, const void *indices);
	void Clear();
private:

};

