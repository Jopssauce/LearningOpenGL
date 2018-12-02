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
#include "VertexArray.h"
#include "stb_image.h"
#include "Texture2D.h"


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
		//I started mine from bottom left
		float vertices[] = {
			//Pos				//Color			//Texture Coords
			-0.5, -0.5, 1.0,	1.0, 0.0, 0.0,	0.0, 0.0,
			0.5,  -0.5, 1.0,	0.0, 1.0, 0.0,	1.0, 0.0,
			0.5,  0.5, 1.0,		0.0, 0.0, 1.0,	1.0, 1.0,
			-0.5, 0.5, 1.0,		1.0, 1.0, 0.0,	0.0, 1.0

		};

		//Index Buffer reuses vertices instead of duplicating them
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		//Vertex Array
		VertexArray vao(1);

		VertexBuffer vb(vertices, 32 * sizeof(float));
		IndexBuffer ib(indices, 6);

		GLErrorCall(glEnableVertexAttribArray(0));
		GLErrorCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (0 * sizeof(float)) ));
		GLErrorCall(glEnableVertexAttribArray(1));
		GLErrorCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (3 * sizeof(float)) ));
		GLErrorCall(glEnableVertexAttribArray(2))
		GLErrorCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (6 * sizeof(float)) ));

		//Create Shader
		Shader shader("res/shaders/Basic.shader");
		//GLErrorCall( shader.SetUniformLocation("u_Color", 1.0, 0.0, 0.0, 1.0));
		//Create Texture2D
		Texture2D texture1("res/images/container.jpg", GL_RGB, true);
		Texture2D texture2("res/images/awesomeface.png", GL_RGBA, true);

		glUniform1i(glGetUniformLocation(shader.id, "texture1"), 0);
		glUniform1i(glGetUniformLocation(shader.id, "texture2"), 1);
	
		Renderer renderer;
		float red = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			glActiveTexture(GL_TEXTURE0);
			texture1.Bind();
			glActiveTexture(GL_TEXTURE1);
			texture2.Bind();

			renderer.Draw(ib, vao, shader, GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			//GLErrorCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			//GLErrorCall(shader.SetUniformLocation("u_Color", red, 0.0, 0.0, 1.0));

			float time = glfwGetTime();
			red = (sin(time) / 2.0f);
			float green = (cos(time) / 2.0f);
			GLErrorCall(shader.SetUniformLocation("offset", red, green, 0.0, 0.0));
		

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	
	glfwTerminate();
	return 0;
}