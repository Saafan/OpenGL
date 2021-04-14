#include "Instancing.h"

#include "Renderer.h"
#include "imgui/imgui.h"
#include "Model.h"
#include "Camera.h"

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


void test::Instancing::OnUpdate(float deltaTime)
{
	static float t;
	static float t2;
	shader->Bind();
	shader->SetModelMatrix(modelMat);
	shader->SetUniform1f("t1", t);
	shader->SetUniform1f("t2", t2);
	t += 0.001f;
	t2 += 0.01f;
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void test::Instancing::OnRender()
{

}

void test::Instancing::OnImGuiRender()
{

}
