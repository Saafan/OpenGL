#pragma once
#include "Texture.h"
#include <iostream>

class Material
{
public:
	Material(Shader* shader, float shininess = 64.0f, Texture* diffuseSmapler = new Texture("images/blank.png"), Texture* specularSampler =  new Texture("images/blank.png"), int diffuseSamplerSlot = 0, int specularSamplerSlot = 1);

	void SetDiffuseSample(Texture* diffuseSmapler, int samplerSlot);
	void SetSpecularSampel(Texture* specularSmapler, int samplerSlot);
	void SetShininess(float shininess);

	void BindMaterial(std::string materialDiffuseName = "", std::string materialSpecularName = "", std::string materialShininessName = "");

private:
	Texture* diffuseTexture = nullptr;
	Texture* specularTexture = nullptr;
	Shader* shader = nullptr;
	float shininess = 64.0f;

	int diffuseSamplerSlot = 0;
	int specularSamplerSlot = 1;

};
