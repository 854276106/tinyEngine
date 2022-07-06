//
// Created by zzn on 22-6-29.
//

#include "Mesh.h"

#include <utility>

Mesh::Mesh(float* vertices)
{
	this->vertices.resize(36);
	memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _faces, std::vector<Texture> _textures)
		:vertices(std::move(_vertices)),faces(std::move(_faces)),textures(std::move(_textures))
{
	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	// bind appropriate textures
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;
	for(Texture& texture:textures)
	{
		glActiveTexture(GL_TEXTURE0 + texture.Slot); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = texture.type;
		if(name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if(name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to string
		else if(name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to string
		else if(name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to string

		// now set the sampler to the correct texture unit
		shader.SetInteger((name + number).c_str(),texture.Slot);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, texture.id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(faces.size()), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,  static_cast<GLsizei>(sizeof(Vertex)*vertices.size()), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  static_cast<GLsizei>(sizeof(Vertex) * vertices.size()), &faces[0], GL_STATIC_DRAW);

	//位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
	// 法向量
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
