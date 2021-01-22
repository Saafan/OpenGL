#pragma once


#include <vector>
#include <string>
#include "Shader.h"
#include "Mesh.h"
#include "stb_image/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

class Model3D
{
public:
	Model3D(const char* path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<MatTexture> textures_loaded;


	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MatTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory);


};