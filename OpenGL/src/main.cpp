#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

#include "Model.h"

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
	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
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

	Shader shader("shaders/LightingShader.shader");
	shader.Bind();

	Camera camera(window, &shader, 2.5f);

	Material mat(&shader, 64.0f);
	Material matGrid(&shader, 256.0f);

	mat.AddTexture("images/container2.png", aiTextureType_DIFFUSE, 1);
	mat.AddTexture("images/container2_specular.png", aiTextureType_SPECULAR, 2);

	Light dirLight(shader, camera, LightType::Point, 0);
	dirLight.SetPointLightParam(glm::vec3(1.0f), glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	dirLight.SetAmbient(1.0f, 1.0f, 1.0f);

	//Model pyramid(ModelType::Pyramid, &shader, &mat);
	//Model pyramid2(ModelType::Pyramid, &shader, &mat);
	//Model ground(ModelType::GroundPlane, &shader, &matGrid);
	//Model ground2(ModelType::GroundPlane, &shader, &matGrid);
	//
	//Model cubeLooker(ModelType::Cube, &shader, &mat);
	
	Model model("models/teapot.obj", &shader);
	model.SetMaterial(mat);

	//ground.Scale(5, 0, 5);
	//ground2.SetGroundPlaneParam(2, 2);
	//ground2.Translate(3, 0, 3);
	//pyramid2.Translate(-1.0, 0, -3);
	//pyramid.Translate(1.0, 0, 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		//Code Here
		camera.CalculateViewMatrix();

		//ground.Render();
		//pyramid.Render();
		//pyramid2.Render();
		//
		//cubeLooker.LookAt(glm::vec3(0, 0, 0));
		//cubeLooker.Render();

		model.Render();

		dirLight.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
