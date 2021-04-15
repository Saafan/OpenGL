#include "Instancing.h"

#include "Renderer.h"
#include "imgui/imgui.h"
#include "Model.h"
#include "Camera.h"

#include "glm/gtx/intersect.hpp"

test::Instancing::Instancing(GLFWwindow* window)
{
	this->window = window;
	OnLoad();
}

test::Instancing::~Instancing()
{

}

Shader* shader = nullptr;
Model* model = nullptr;
Camera* camera = nullptr;

VertexBuffer* vb = nullptr;
VertexBufferLayout* vbl = nullptr;
VertexArray* va = nullptr;

float quadVertices[] = {
	// positions     // colors
	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};


float quad[]{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	-1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
};

glm::mat4 modelMat(1.0f);
Shader* lightingShader = nullptr;
void test::Instancing::OnLoad()
{
	shader = new Shader("shaders/Instancing.shader");


	model = new Model(ModelType::Cube, shader);
	vb = new VertexBuffer(quad, sizeof(quad));
	vbl = new VertexBufferLayout;
	vbl->Push<float>(3);
	va = new VertexArray();
	va->AddBuffer(*vb, *vbl);
}

std::vector<glm::vec3> offsets{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.5f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.5f, 0.0f)
};

float yaw, pitch;
void test::Instancing::OnUpdate(float deltaTime)
{
	
	shader->Bind();
	shader->SetModelMatrix(modelMat);

	shader->SetUniform1f("yaw", yaw);
	shader->SetUniform1f("pitch", pitch);


	//shader->SetUniform1f("t", t);

	//t += 0.1f;
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void test::Instancing::OnRender()
{

}

void test::Instancing::OnImGuiRender()
{
	static float lastTime;
	float fps = 1 / (glfwGetTime() - lastTime);
	glfwSwapInterval(1);
	
	lastTime = glfwGetTime();

	ImGui::DragFloat("Pitch", &pitch);
	ImGui::DragFloat("Yaw", &yaw);


	ImGui::Text("%f", fps);

}
