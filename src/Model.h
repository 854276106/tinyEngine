//
// Created by zzn on 22-7-3.
//

#ifndef TINYENGINE_MODEL_H
#define TINYENGINE_MODEL_H

#include <iostream>
#include <vector>
#include <string>
#include "Mesh.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
	Model()=default;
	~Model()=default;
	void Draw(Shader& shader);
public:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
private:
	friend class ResourceManager;
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};


#endif //TINYENGINE_MODEL_H
