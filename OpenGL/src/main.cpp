#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "GLFW Initialization Failed!" << std::endl;
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "GLFW Window Initialization Failed!" << std::endl;
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Initialization Failed!" << std::endl;
		return -1;
	}


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);

		//Code Here


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
