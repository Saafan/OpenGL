#pragma once
#include "gl/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Material.h"
#include "IndexBuffer.h"
#include <iostream>

enum class ModelType
{
	Model = 0,
	Line = 1,
	Triangle = 2,
	Plane = 3,
	Cube = 4,
	Pyramid = 5,
	GroundPlane = 6
};

struct ModelMatrices
{
	glm::vec3 scale;
	glm::quat orientation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
};

class Model
{
public:
	Model(ModelType type = ModelType::Model, Shader* shader = nullptr, Material* material = nullptr, float data[] = nullptr, unsigned int size = 0, unsigned int axisNum = 0, unsigned int normalsNum = 0, unsigned int extureCoordNum = 0, GLenum targetBufferObject = GL_TRIANGLES);

	void UpdateIndiciesNum();
	void SetVertexBuffer(const float data[] = nullptr, const unsigned int size = 0);
	void SetVBData(const float data[] = nullptr);
	void SetVBSize(const unsigned int size);
	void SetVBAttributes(const unsigned int axisNum, const  unsigned int normalsNum = 0, const  unsigned int textureCoordNum = 0);
	void SetShader(Shader& shader);
	void SetMaterial(Material& material);
	void SetTargetBufferObject(const GLenum target);

	glm::mat4& GetModelMatrix();

	//Setting Primitives Parameters
	void SetTriangleParam(const float width = 0.5f, const float length = 0.5f);
	void SetTriangleParam(const float triangleSideLength);
	void SetPlaneParam(const float width = 0.5f, const float length = 0.5f);
	void SetPlaneParam(const float planeSideLength);
	void SetGroundPlaneParam(const float width = 0.5f, const float length = 0.5f);
	void SetGroundPlaneParam(const float planeSideLength);
	void SetCubeParam(const float length = 0.5f, const float width = 0.5f, const float height = 0.5f);
	void SetCubeParam(const float cubeSideLength);
	void SetPyramidParam(const float length = 0.5f, const float width = 0.5f, const float height = 0.5f);
	void SetPyramidParam(const float pyramidSideLength);

	//Transformations
	glm::mat4& Translate(float x, float y, float z);
	glm::mat4& Rotate(float angle, float xAxis, float yAxis, float zAxis);
	glm::mat4& Scale(float x, float y, float z);
	glm::mat4& Scale(float uniformScaleFactor);
	glm::mat4& TranslateAccum(float x, float y, float z);
	glm::mat4& RotateAccum(float angle, float xAxis, float yAxis, float zAxis);
	glm::mat4& ScaleAccum(float x, float y, float z);

	//Transformations with glm references
	glm::mat4& Translate(glm::vec3 pos);
	glm::mat4& Rotate(float angle, glm::vec3 axis);
	glm::mat4& Scale(glm::vec3 factor);
	glm::mat4& TranslateAccum(glm::vec3 pos);
	glm::mat4& RotateAccum(float angle, glm::vec3 axis);
	glm::mat4& ScaleAccum(glm::vec3 factor);

	//Transformations Features
	void LookAt(glm::vec3 center);
	void LookAt(Model& centerObj);
	void Decompose(glm::mat4& model);
	void Decompose();

	void Render(std::string modelUniformName = DEFAULT_UNIFORM_MODEL_NAME);
	void RenderLine(const glm::vec3 startPoint, const glm::vec3 endPoint, float lineWidth = 2.5f);
	void RenderLine(const float startX, const float startY, const float startZ, const float endX, const float endY, const float endZ, float lineWidth = 2.5f);
	void RenderWireCone(const glm::vec3 startPoint, const glm::vec3 endPoint, float angle, float lineWidth = 2.5f);
private:
	ModelType type;

	Shader* shader = nullptr;
	Material* material = nullptr;
	glm::mat4 model = glm::mat4(1.0f);

	//this matrix for saving the decompositions of model matrix
	ModelMatrices* modelMatrices = nullptr;

	VertexBuffer* vb = nullptr;
	VertexBufferLayout* vbl = nullptr;
	VertexArray* va = nullptr;

	GLenum targetBufferObject;

	unsigned int indicesNum = 0;
	unsigned int axisNum = 0, normalsNum = 0, textureCoordNum = 0;
	const void* data = nullptr;
	unsigned int dataSize = 0.0f;


};