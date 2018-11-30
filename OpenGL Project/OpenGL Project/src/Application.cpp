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
#include "Shader.h"


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
	{
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
		GLErrorCall(glGenVertexArrays(1, &vao));
		GLErrorCall(glBindVertexArray(vao));

		VertexBuffer vb(vertices, 8 * sizeof(float));
		IndexBuffer ib(indices, 6);

		GLErrorCall(glEnableVertexAttribArray(0));
		GLErrorCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

		//Create Shader
		Shader shader("res/shaders/Basic.shader");
		GLErrorCall( shader.SetUniformLocation("u_Color", 1.0, 0.0, 0.0, 1.0));
		

		float red = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			GLErrorCall(glBindVertexArray(vao));
			ib.Bind();
			shader.Bind();

			GLErrorCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			GLErrorCall(shader.SetUniformLocation("u_Color", red, 0.0, 0.0, 1.0));


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
	}
	
	glfwTerminate();
	return 0;
}