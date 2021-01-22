#pragma once
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

template <typename T = float>
struct vec2
{
	T x = 0.0f;
	T y = 0.0f;
};

class Camera
{
public:
	Camera(GLFWwindow* window, Shader* cameraShader, float speed = 2.5f, unsigned int viewUniformLocation = 0, unsigned int projUniformLocation = 0);

	void SetCameraPositionUniform(std::string uniformName);
	std::string& GetCameraPositionUniform();

	void SetSpeed(float speed);
	void SetCursorLock(bool locked);
	void SetWindow(GLFWwindow* window);
	glm::mat4 SetProjectionMatrix(unsigned int projUniformLocation, float width, float height, float fovAngle);
	void SetViewUniformLocation(unsigned int viewUniformLocation);
	glm::mat4& CalculateViewMatrix();

	std::string cameraPositionUniform = "viewPos";
	
	float pitch = 0.0f;
	float yaw = -90.0f;
	GLFWwindow* window;
	Shader* cameraShader = nullptr;

	unsigned int viewUniformLocation = -1;
	unsigned int projUniformLocation = -1;
	glm::mat4* viewMatrix = nullptr;
	glm::mat4* projMatrix = nullptr;

	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static float speed;
	static glm::vec2 mouseDelta;
};