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
		
		//Generate Texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		//Texture Wrapping
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//Texture Filtering
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//Load Image
		int width, height, nrChannels;
		unsigned char *data = stbi_load("res/images/container.jpg", &width, &height, &nrChannels, 0);
		if(data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cout << "ERROR: " << "Could not load texture" << endl;
		}
		stbi_image_free(data);
		





		Renderer renderer;
		float red = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			glBindTexture(GL_TEXTURE_2D, texture);
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