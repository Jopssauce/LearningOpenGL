#include "Shader.h"

ShaderProgramSource Shader::ParseShader(const string filepath)
{
	ifstream stream(filepath);
	//2 arrays of strings
	stringstream ss[2];

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	string line;
	while (getline(stream, line))
	{
		//Find Per line Shader
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		//Insert new line to sstream
		else
		{
			ss[int(type)] << line << '\n';
		}
	}
	//Returns struct
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const string & source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	//Replaces default shader with source shader
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	//Error Handling
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const string & vertexShader, const string & fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//Attaches Shader to program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	//Specifies to use the shader attached to program
	glLinkProgram(program);
	glValidateProgram(program);

	//Flags Shader to be deleted to free memory
	//Shader will not be deleted as long as it is attached to a program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::SetUniformLocation(const string &name, float v1, float v2, float v3, float v4)
{
	//Passing data from cpu to gpu once shader setup is done
	int location = glGetUniformLocation(id, name.c_str());
	//Break if location not found
	if (location == -1) cout << name << " Not found" << endl;
		glUniform4f(location, 1.0, 0.0, 0.0, 1.0);
}

Shader::Shader(const string &filepath)
{
	ShaderProgramSource source = ParseShader(filepath);
	id = CreateShader(source.vertexSource, source.fragmentSrouce);
}

Shader::~Shader()
{
	GLErrorCall(glDeleteProgram(id));
}

void Shader::Bind()
{
	GLErrorCall(glUseProgram(id));
}

void Shader::Unbind()
{
	GLErrorCall(glUseProgram(0));
}

