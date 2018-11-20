#pragma once
#include "GL/glew.h"


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
