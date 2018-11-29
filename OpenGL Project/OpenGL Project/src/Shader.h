#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"

using namespace std;

struct ShaderProgramSource
{
	string vertexSource;
	string fragmentSrouce;
};

class Shader
{
private:
	ShaderProgramSource ParseShader(const string filepath);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
public:
	unsigned int id;
	void SetUniformLocation(const string &name, float v1 = 1.0, float v2 = 1.0, float v3 = 1.0, float v4 = 1.0);
	Shader(const string &filepath);
	~Shader();
	void Bind();
	void Unbind();
};