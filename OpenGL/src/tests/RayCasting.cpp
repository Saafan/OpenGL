#include "RayCasting.h"
#include "Camera.h"
#include "imgui/imgui.h"
#include "glm/gtx/intersect.hpp"
#include "Model.h"
#include "Light.h"
#include "../PrimitivesData.h"

test::RayCasting::RayCasting(GLFWwindow* window)
{
	this->window = window;
	OnLoad();
}

test::RayCasting::~RayCasting()
{

}

bool RayIntersectPlane()
{
	return false;
}

Shader* singleQuadShader = nullptr;
Shader* sceneShader = nullptr;
Camera* camera = nullptr;
Light* light = nullptr;
Material* mat = nullptr;
Material* matGrid = nullptr;
Model* model = nullptr;
Model* plane = nullptr;
Model* testCube = nullptr;

Model* quad = nullptr;

bool RayIntersectTriangle(glm::vec3 point)
{
	std::vector<glm::vec3> vert;
	for (size_t i = 0; i < triangleVerticies.size(); i++)
		vert.push_back(glm::vec3(model->GetModelMatrix() * triangleVerticies[i]));

	glm::vec3 a, b, c;

	a = glm::normalize(glm::cross(glm::normalize(point - vert[0]), glm::normalize(point - vert[1])));
	b = glm::normalize(glm::cross(glm::normalize(point - vert[1]), glm::normalize(point - vert[2])));
	c = glm::normalize(glm::cross(glm::normalize(point - vert[2]), glm::normalize(point - vert[0])));

	if (a.z > 0 || b.z > 0 || c.z > 0)
		return false;

	return true;
}

void AttachTextureToFrameBuffer()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

GLchar data[WIDTH * HEIGHT * 4];

float quadVertices[] = {
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};


unsigned int fbo;
unsigned int texColorBuffer;
unsigned int rbo;

void test::RayCasting::OnLoad()
{
	
	singleQuadShader = new Shader("shaders/SingleQuad.shader");
	sceneShader = new Shader("shaders/LightingShader.shader");
	singleQuadShader->Bind();


	camera = new Camera(window, sceneShader);
	light = new Light(*sceneShader, *camera, LightType::Spot);
	light->SetSpotLightParam(glm::vec3(3.0f), glm::vec3(-3.0f), glm::vec3(0.8f), glm::vec3(0.4f), glm::vec3(1.0f));
	model = new Model(ModelType::Cube, sceneShader);
	plane = new Model(ModelType::GroundPlane, sceneShader);
	
	mat = new Material(sceneShader);
	mat->AddTexture("images/container2.png", aiTextureType_DIFFUSE, 0);
	mat->AddTexture("images/container2_specular.png", aiTextureType_SPECULAR, 1);

	matGrid = new Material(sceneShader);
	matGrid->AddTexture("images/grid2.jpg", aiTextureType_DIFFUSE, 0);
	
	model->Translate(1, 0, -5);

	
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);


	//Generate a Texture

	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DrawScene()
{
	sceneShader->Bind();

	camera->CalculateViewMatrix();
	light->Render();
	model->SetMaterial(*mat);
	model->Render();

	plane->SetMaterial(*matGrid);
	plane->Render();


}

void test::RayCasting::OnUpdate(float deltaTime)
{


	//first Pass
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawScene();



	//Second Pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	singleQuadShader->Bind();
	VertexBuffer vb(quadVertices, sizeof(quadVertices));
	VertexBufferLayout vbl;
	vbl.Push<float>(2);
	vbl.Push<float>(2);

	VertexArray va;
	va.AddBuffer(vb, vbl);
	va.Bind();
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void test::RayCasting::OnRender()
{

}

void test::RayCasting::OnImGuiRender()
{

}
