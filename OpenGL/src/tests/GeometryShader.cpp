#include "GeometryShader.h"

#include "imgui/imgui.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"
#include "Material.h"
#include "Light.h"

test::GeometryShader::GeometryShader(GLFWwindow* window)
{
	this->window = window;
	OnLoad();
}

test::GeometryShader::~GeometryShader()
{

}

Texture* cubeMapTexture;
Shader* geometryShader;
Shader* shader;
Shader* cubeMapShader;
Camera* camera;

Model* model;
Model* modelGeo;

Material* mat;

Light* light;

VertexBuffer* vb;
VertexBufferLayout* vbl;
VertexArray* va;


float points[]
{
	-0.5f, -0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f,	 0.0f,
};




void test::GeometryShader::OnLoad()
{
	geometryShader = new Shader("shaders/GeometryShader.shader");
	shader = new Shader("shaders/LightingShader.shader");
	camera = new Camera(window, shader);

	model = new Model("models/teapot/teapot.obj", shader);
	modelGeo = new Model("models/teapot/teapot.obj", geometryShader);

	vb = new VertexBuffer(points, sizeof(points));
	vbl = new VertexBufferLayout();
	vbl->Push<float>(3);

	va = new VertexArray();
	va->AddBuffer(*vb, *vbl);
}

glm::mat4 view, proj;
void test::GeometryShader::OnUpdate(float deltaTime)
{
	geometryShader->Bind();
	geometryShader->SetViewMatrix(view);
	geometryShader->SetProjMatrix(proj);
	modelGeo->Render();

	camera->CalculateViewMatrix();
	shader->Bind();
	model->Render();

	view = camera->GetCameraViewMatrix();
	proj = *camera->projMatrix;

}

void test::GeometryShader::OnRender()
{

}

void test::GeometryShader::OnImGuiRender()
{

}
