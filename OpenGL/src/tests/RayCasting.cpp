#include "RayCasting.h"
#include "Camera.h"
#include "imgui/imgui.h"
#include "Model.h"
#include "Light.h"

test::RayCasting::RayCasting(GLFWwindow* window)
{
	this->window = window;
	OnLoad();
}

test::RayCasting::~RayCasting()
{

}

Shader* shader = nullptr;
Camera* camera = nullptr;
Light* light = nullptr;
Material* mat = nullptr;
Model* model = nullptr;

void test::RayCasting::OnLoad()
{
	shader = new Shader("shaders/LightingShader.shader");
	camera = new Camera(window, shader);
	//camera->SetCursorLock(false);
	light = new Light(*shader, *camera, LightType::Spot);
	light->SetSpotLightParam(glm::vec3(1.0f), glm::vec3(-1.0f), glm::vec3(0.4f), glm::vec3(0.6f), glm::vec3(0.8f));
	light->SetPosition(glm::vec3(1.0f));
	mat = new Material(shader);
	mat->AddTexture("images/container2.png", aiTextureType_DIFFUSE, 0);
	mat->AddTexture("images/container2_specular.png", aiTextureType_SPECULAR, 1);
	model = new Model(ModelType::Pyramid, shader, mat);
}

void test::RayCasting::OnUpdate(float deltaTime)
{
	camera->CalculateViewMatrix();
	light->Render();
	glPointSize(100);
	glBegin(GL_POINTS);
	glVertex3f(camera->RayCast(3).x, camera->RayCast(3).y, camera->RayCast(3).z);
	glEnd();
	model->Render();
	std::cout << "(x: " << camera->RayCast(3).x << ", y:" << camera->RayCast(3).y << ", z:" << camera->RayCast(3).z << ")" << std::endl;
}

void test::RayCasting::OnRender()
{

}

void test::RayCasting::OnImGuiRender()
{

}
