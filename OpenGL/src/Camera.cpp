#include "Camera.h"
#include <iostream>

glm::vec3 Camera::cameraPos = glm::vec3(1.0f);
glm::vec3 Camera::cameraFront = glm::vec3(0.0f);
float Camera::speed = 2.5f;
glm::vec2 Camera::mouseDelta = glm::vec2(0.0f);


float GetDeltaTime()
{
	static float currentTime = 0.0f;
	static float oldTime = 0.0f;
	float deltaTime = 0.0f;
	currentTime = glfwGetTime();
	deltaTime = currentTime - oldTime;
	oldTime = glfwGetTime();
	return deltaTime;
}

void HandleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			Camera::cameraPos += Camera::cameraFront;
		if (key == GLFW_KEY_S)
			Camera::cameraPos -= Camera::cameraFront;

		glm::vec3 right = glm::cross(Camera::cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));

		if (key == GLFW_KEY_A)
			Camera::cameraPos -= right;
		if (key == GLFW_KEY_D)
			Camera::cameraPos += right;
	}
}

void HandleMouseInput(GLFWwindow* window, double xPos, double yPos)
{
	static glm::vec2 oldMosuePos;
	static glm::vec2 currentMosuePos;

	static bool firstTime = true;

	static glm::vec2 oldMousePos;
	static glm::vec2 currentMousePos;

	currentMousePos.x = (float)xPos;
	currentMousePos.y = (float)yPos;

	if (!firstTime)
	{
		Camera::mouseDelta.x = -(oldMousePos.x - currentMousePos.x);
		Camera::mouseDelta.y = (oldMousePos.y - currentMousePos.y);
	}
	else
		firstTime = false;

	oldMousePos.x = (float)xPos;
	oldMousePos.y = (float)yPos;
}




Camera::Camera(GLFWwindow* window, Shader* shader, float speed, unsigned int viewUniformLocation, unsigned int projUniformLocation)
{
	this->window = window;
	this->speed = speed;
	this->cameraShader = shader;
	this->viewUniformLocation = viewUniformLocation;
	glfwSetKeyCallback(this->window, HandleKeyboardInput);
	glfwSetCursorPosCallback(this->window, HandleMouseInput);
	SetCursorLock(true);

	if (projUniformLocation != -1)
		SetProjectionMatrix(projUniformLocation, WIDTH, HEIGHT, 60.0f);

	CalculateViewMatrix();
}


void Camera::SetCameraPositionUniform(std::string uniformName)
{
	if (uniformName.empty())
		return;
	cameraPositionUniform = uniformName;
}

std::string& Camera::GetCameraPositionUniform()
{
	return cameraPositionUniform;
}

void Camera::SetSpeed(float speed)
{
	this->speed = speed;
}

void Camera::SetCursorLock(bool locked)
{
	glfwSetInputMode(window, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Camera::SetWindow(GLFWwindow* window)
{
	this->window = window;
}

glm::mat4 Camera::SetProjectionMatrix(unsigned int projUniformLocation, float width, float height, float fovAngle)
{
	if (cameraShader)
		cameraShader->Bind();
	glm::mat4* projMat = new glm::mat4(1.0f);
	*projMat = glm::perspective(glm::radians(fovAngle), width / height, 0.1f, 1000.0f);
	this->projUniformLocation = projUniformLocation;

	if (this->projUniformLocation != -1)
		cameraShader->SetProjMatrix(*projMat);
	this->projMatrix = projMat;
	return *projMat;
}

void Camera::SetViewUniformLocation(unsigned int viewUniformLocation)
{
	this->viewUniformLocation = viewUniformLocation;
}

glm::mat4& Camera::CalculateViewMatrix()
{
	if (cameraShader)
		cameraShader->Bind();

	float deltaTime = GetDeltaTime();
	float totalSpeed = speed * deltaTime;

	mouseDelta.x *= totalSpeed;
	mouseDelta.y *= totalSpeed;
	yaw += mouseDelta.x;
	pitch += mouseDelta.y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cameraFront.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	cameraFront.y = std::sin(glm::radians(pitch));
	cameraFront.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

	cameraFront = glm::normalize(cameraFront);
	//#OPTIMIZE 
	glm::mat4* viewMat = new glm::mat4(1.0f);
	*viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
	if (viewUniformLocation != -1)
		cameraShader->SetViewMatrix(*viewMat);

	viewMatrix = viewMat;

	return *viewMat;
}

