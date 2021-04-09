#include "CubeMap.h"

#include "imgui/imgui.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"
#include "Material.h"
#include "Light.h"


float skyboxVertices2[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

test::CubeMap::CubeMap(GLFWwindow* window)
{
	this->window = window;
	OnLoad();
}

test::CubeMap::~CubeMap()
{

}

Texture* cubeMapTexture;
Shader* shader;
Shader* cubeMapShader;
Camera* camera;

Model* model;

Material* mat;

Light* light;

//#TODO Create CubeMap Model for Model Class

void test::CubeMap::OnLoad()
{
	
	shader = new Shader("shaders/LightingShader.shader");
	cubeMapShader = new Shader("shaders/CubeMap.shader");
	std::vector<std::string> tex;
	camera = new Camera(window, shader);
	tex.push_back("images/right.jpg");
	tex.push_back("images/left.jpg");
	tex.push_back("images/top.jpg");

	tex.push_back("images/bottom.jpg");
	tex.push_back("images/front.jpg");
	tex.push_back("images/back.jpg");

	cubeMapTexture = new Texture(tex);
	mat = new Material(shader,128.0f);
	mat->AddTexture("images/container2.png", aiTextureType_DIFFUSE,10);
	mat->AddTexture("images/container2_specular.png", aiTextureType_SPECULAR,11);
	mat->AddTexture("images/container2_reflection.png", aiTextureType_REFLECTION,12);
	model = new Model(ModelType::Cube, shader, mat);

	light = new Light(*shader, *camera, LightType::Spot);
	light->SetSpotLightParam(glm::vec3(2.0f), glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec3(0.4f), glm::vec3(0.7f));

}
glm::mat4 proj;
glm::mat4 view;
void test::CubeMap::OnUpdate(float deltaTime)
{
	glDepthMask(GL_FALSE);
	cubeMapShader->Bind();
	cubeMapShader->SetViewMatrix(view);
	cubeMapShader->SetProjMatrix(proj);
	VertexBuffer vb(skyboxVertices2, sizeof(skyboxVertices2));
	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	VertexArray va;
	va.AddBuffer(vb, vbl);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture->GetTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glDepthMask(GL_TRUE);
	proj = *(camera->projMatrix);
	camera->CalculateViewMatrix();
	shader->Bind();
	model->Render();
	light->Render();
	view = glm::mat4(glm::mat3(camera->GetCameraViewMatrix()));
}

void test::CubeMap::OnRender()
{

}

void test::CubeMap::OnImGuiRender()
{

}
