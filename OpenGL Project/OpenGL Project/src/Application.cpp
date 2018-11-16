#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//MACROS
//Break if false
#define ASSERT(x) if (!(x)) __debugbreak();
//Calls Clear then the function to check for errors then GLLogCall
#define GLErrorCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//NOTE: Improve this soon using OpenGL Debug Output
static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
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

	//Store data in buffers to be used by shaders
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//Initializes buffer data to store
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

	unsigned int ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	//Initializes buffer data to store
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//Sets the type of what the buffer contains
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); \
	
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

		GLErrorCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		glUniform4f(location, red, 0.0, 0.0, 1.0);
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