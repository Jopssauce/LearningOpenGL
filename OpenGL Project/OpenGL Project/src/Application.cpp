#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
	window = glfwCreateWindow(800, 600, "RIVERA ENGINE", NULL, NULL);
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
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		};
		//Index Buffer reuses vertices instead of duplicating them
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20

		};

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		//Vertex Array
		VertexArray vao(1);

		VertexBuffer vb(vertices,sizeof(vertices));
		IndexBuffer ib(indices, sizeof(indices));

		GLErrorCall(glEnableVertexAttribArray(0));
		GLErrorCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (0 * sizeof(float)) ));
		//GLErrorCall(glEnableVertexAttribArray(1));
		//GLErrorCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (3 * sizeof(float)) ));
		GLErrorCall(glEnableVertexAttribArray(2))
		GLErrorCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (3 * sizeof(float)) ));

		//Create Shader
		Shader shader("res/shaders/Basic.shader");

		//GLErrorCall( shader.SetUniformLocation("u_Color", 1.0, 0.0, 0.0, 1.0));
		//Create Texture2D
		Texture2D texture1("res/images/container.jpg", GL_RGB, true);
		Texture2D texture2("res/images/head.png", GL_RGBA, true);

		glUniform1i(glGetUniformLocation(shader.id, "texture1"), 0);
		glUniform1i(glGetUniformLocation(shader.id, "texture2"), 1);


		Renderer renderer;
		float red = 0.0f;
		float increment = 0.05f;

		
		glEnable(GL_DEPTH_TEST);
		

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();
			float time = glfwGetTime();
			glActiveTexture(GL_TEXTURE0);
			texture1.Bind();
			glActiveTexture(GL_TEXTURE1);
			texture2.Bind();

			//MVP
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			
			glm::mat4 view;
			glm::mat4 projection;
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
			
			unsigned int viewLoc = glGetUniformLocation(shader.id, "view");
			unsigned int projectionLoc = glGetUniformLocation(shader.id, "projection");

			
			GLErrorCall(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
			GLErrorCall(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)));

			for (int i = 0; i < 10; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, glm::radians(20.0f * i + 1) * (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

				unsigned int modelLoc = glGetUniformLocation(shader.id, "model");
				GLErrorCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]));
				renderer.Draw(ib, vao, shader, GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);
			}

		

			
			
		

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	
	glfwTerminate();
	return 0;
}