//
// Created by zzn on 22-5-12.
//

#ifndef DEMO_RESOURCEMANAGER_H
#define DEMO_RESOURCEMANAGER_H

#include <map>
#include <string>
#include "Shader.h"
#include "Texture2D.h"
#include "Model.h"


class ResourceManager
{
public:
	static Shader LoadShader(const GLchar* vertexShaderFile,const GLchar* fragmentShaderFile,
			const GLchar* geometryShaderFile,const std::string& name);

	static Shader GetShader(const std::string& name);

	static Texture2D LoadTexture(const GLchar* file, GLboolean alpha, const std::string& name,int textureSlot);

	static Texture2D GetTexture(const std::string& name);

	static Model LoadModel(const GLchar* file,const std::string& name);

	static Model GetModel(const std::string& name);

	static void Clear();

private:
	// Resource storage（存储资源）
	static std::map<std::string,Shader>Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Model> Models;

	ResourceManager()=default;

	static Shader LoadShaderFromFile(const GLchar* vertexShaderFilePath,const GLchar* fragmentShaderFilePath,
			const GLchar* geometryShaderFilePath= nullptr);

	static Texture2D LoadTextureFromFile(const GLchar* file, GLboolean alpha,int textureSlot);

	static Model LoadModelFromFile(const GLchar* file);
};


#endif //DEMO_RESOURCEMANAGER_H
