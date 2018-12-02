#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <iostream>

using namespace std;

class Texture2D
{
public:
	unsigned int id;
	Texture2D(const string &file);
	~Texture2D();
	void Bind();
	void Unbind();

private:
	void WrapTexture();
	void FilterTexture();
	void LoadImage(const string &file);

};

