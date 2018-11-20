#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource
{
	string vertexSource;
	string fragmentSrouce;
};

static ShaderProgramSource ParseShader(const string filepath)
{
	ifstream stream(filepath);
	//2 arrays of strings
	stringstream ss[2];

	enum class ShaderType
	{NONE = -1, VERTEX = 0, FRAGMENT = 1};
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
	return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const string& source)
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

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) cout << "Im sad now" << endl;
	cout << glGetString(GL_VERSION) << endl;

	glfwSwapInterval(1);

	//Counter Clockwise
	float vertices[] = {
		-0.5, -0.5,
		0.5,  -0.5,
		0.5,   0.5,
		-0.5, 0.5,
		
	};

	//Index Buffer reuses vertices instead of duplicating them
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	//Vertex Array
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexBuffer vb(vertices, 4 * 2 * sizeof(float));
	IndexBuffer ib(indices, 6);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	//Create Shader
	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(source.vertexSource, source.fragmentSrouce);
	glUseProgram(shader);

	//Passing data from cpu to gpu once shader setup is done
	int location = glGetUniformLocation(shader, "u_Color");
	//Break if location not found
	ASSERT(location != -1)
	glUniform4f(location, 1.0, 0.0, 0.0, 1.0);

	float red = 0.0f;
	float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		GLErrorCall(glBindVertexArray(vao));
		GLErrorCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		glUniform4f(location, red, 0.0, 0.0, 1.0);
		GLErrorCall(glBindVertexArray(0));

		if (red > 1.0f)
		{
			increment -= 0.05f;
		}
		else if (red < 0.0f)
		{
			increment += 0.05f;
		}
		red += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}