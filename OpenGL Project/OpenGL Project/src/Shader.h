#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
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
	unordered_map <string, int> uniformLocationCache;
public:
	unsigned int id;
	Shader(const string &filepath);
	~Shader();
	void Bind();
	void Unbind();
	void SetUniformLocation(const string &name, float v1 = 1.0, float v2 = 1.0, float v3 = 1.0, float v4 = 1.0);
	int GetUniformLocation(const string &name);


};