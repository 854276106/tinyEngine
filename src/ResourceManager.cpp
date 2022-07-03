//
// Created by zzn on 22-5-12.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Instantiate static variables
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile,
		const GLchar* geometryShaderFile, std::string name)
{
	Shaders.insert(std::make_pair(name,
			LoadShaderFromFile(vertexShaderFile,
					fragmentShaderFile,geometryShaderFile))) ;
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha, std::string name,int textureSlot)
{
	Textures.insert(std::make_pair(name,LoadTextureFromFile(file, alpha,textureSlot)));
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

Shader ResourceManager::LoadShaderFromFile(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath,
		const GLchar* geometryShaderFilePath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vertexShaderFilePath);
		std::ifstream fragmentShaderFile(fragmentShaderFilePath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (geometryShaderFilePath != nullptr)
		{
			std::ifstream geometryShaderFile(geometryShaderFilePath);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar* vertexShaderCode = vertexCode.c_str();
	const GLchar* fragmentShaderCode = fragmentCode.c_str();
	const GLchar* geometryShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vertexShaderCode, fragmentShaderCode, geometryShaderFilePath != nullptr ? geometryShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha,int textureSlot)
{
	// Load image
	int width, height;
	int nrComponents;
	unsigned char* image = stbi_load(file, &width, &height, &nrComponents, 0);
	GLenum format;
	switch (nrComponents)
	{
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		break;
	}

	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Image_Format = GL_RGBA;
	}
	texture.Slot=textureSlot;
	// Now generate texture
	texture.Generate(width, height, image, format);
	// And finally free image data
	//stbi_image_free(image);
	return texture;
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders
	for (auto iter: Shaders)
		glDeleteProgram(iter.second.ShaderID);
	// (Properly) delete all textures
	for (auto iter: Textures)
	{
		glDeleteTextures(1, &iter.second.TextureID);
	}
}