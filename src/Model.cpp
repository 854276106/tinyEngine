//
// Created by zzn on 22-7-3.
//
#include "Model.h"
#include "ResourceManager.h"

void Model::Draw(Shader& shader)
{
	for (auto & mesh : meshes)
	{
		mesh.Draw(shader);
	}
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	std::cout << "mNumMeshes:" << node->mNumMeshes << std::endl;
	std::cout << "mNumChildren:" << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		std::cout << "mNumMeshes->i:" << i << std::endl;
  		aiMesh* currMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back(processMesh(currMesh,scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		std::cout << "mNumChildren->i:" << i << std::endl;
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempFaces;
	std::vector<Texture> tempTextures;

	glm::vec3 temVec;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tempVertex{};

		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			tempVertex.Normal.x = mesh->mNormals[i].x;
			tempVertex.Normal.y = mesh->mNormals[i].y;
			tempVertex.Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0] != nullptr)
		{
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		tempVertices.emplace_back(tempVertex);
	}

	for (unsigned int j = 0; j < mesh->mNumFaces; j++)
	{
		for (unsigned int k = 0; k < mesh->mFaces[j].mNumIndices; k++)
		{
			tempFaces.emplace_back(mesh->mFaces[j].mIndices[k]);
		}
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	tempTextures.insert(tempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	tempTextures.insert(tempTextures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	tempTextures.insert(tempTextures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	tempTextures.insert(tempTextures.end(), heightMaps.begin(), heightMaps.end());

	return {tempVertices,tempFaces,tempTextures};
}

std::vector <Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for(int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for(auto & texture : textures_loaded)
		{
			if(std::strcmp(texture.path.data(), str.C_Str()) == 0)
			{
				textures.emplace_back(texture);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if(!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			//texture.id = TextureFromFile(str.C_Str(), this->directory);
			std::string temp=this->directory;
			std::string textureName=temp.erase(0, temp.find_last_of('/')+1);
			texture.id = ResourceManager::LoadTexture((this->directory+'/'+str.C_Str()).c_str(),GL_TRUE,textureName,i).TextureID;
			texture.Slot=i;
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.emplace_back(texture);
			textures_loaded.emplace_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

