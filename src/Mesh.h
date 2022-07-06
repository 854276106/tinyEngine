//
// Created by zzn on 22-6-29.
//

#ifndef TINYENGINE_MESH_H
#define TINYENGINE_MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <glad/glad.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	int Slot;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	explicit Mesh(float vertices[]);
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _faces, std::vector<Texture> _textures);
	~Mesh()=default;
public:
	/*  网格数据  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> faces;
	std::vector<Texture> textures;
public:
	void Draw(Shader& shader);
private:
	/*  渲染数据  */
	unsigned int VAO{}, VBO{}, EBO{};
	void setupMesh();
};

#endif //TINYENGINE_MESH_H
