#include "Material.h"


Material::Material(Shader* shader, float shininess, Texture* diffuseSmapler, Texture* specularSampler, int diffuseSamplerSlot, int specularSamplerSlot)
{
	this->shininess = shininess;
	this->diffuseTexture = diffuseSmapler;
	this->specularTexture = specularSampler;
	this->diffuseSamplerSlot = diffuseSamplerSlot;
	this->specularSamplerSlot = specularSamplerSlot;
	this->shader = shader;
}

void Material::SetDiffuseSample(Texture* diffuseSmapler, int samplerSlot)
{
	this->diffuseTexture = diffuseSmapler;
	this->diffuseSamplerSlot = diffuseSamplerSlot;
}

void Material::SetSpecularSampel(Texture* specularSmapler, int samplerSlot)
{
	this->specularTexture = specularTexture;
	this->specularSamplerSlot = specularSamplerSlot;
}

void Material::SetShininess(float shininess)
{
	this->shininess = shininess;
}

void Material::BindMaterial(std::string materialDiffuseName, std::string materialSpecularName, std::string materialShininessName)
{
	if (diffuseTexture)
		diffuseTexture->Bind(diffuseSamplerSlot);
	if (specularTexture)
		specularTexture->Bind(specularSamplerSlot);
	if (shader)
	{
		if (materialDiffuseName.empty())
			shader->SetUniform1i("material.diffuse", diffuseSamplerSlot);
		else
			shader->SetUniform1i(materialDiffuseName, diffuseSamplerSlot);

		if (materialSpecularName.empty())
			shader->SetUniform1i("material.specular", specularSamplerSlot);
		else
			shader->SetUniform1i(materialSpecularName, specularSamplerSlot);

		if (materialShininessName.empty())
			shader->SetUniform1f("material.shininess", shininess);
		else
			shader->SetUniform1f(materialShininessName, shininess);
	}
	else
		std::cout << "Shader isn't bound yet" << std::endl;
}

