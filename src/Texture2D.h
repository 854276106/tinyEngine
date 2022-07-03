//
// Created by zzn on 22-5-12.
//

#ifndef DEMO_TEXTURE2D_H
#define DEMO_TEXTURE2D_H

#include <glad/glad.h>

class Texture2D
{
public:
	GLuint TextureID{};

	int Slot;

	// Texture Format
	GLuint Internal_Format;
	GLuint Image_Format;

	// Texture configuration
	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

	Texture2D();

	// Generates texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data, GLenum format);

	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;

};


#endif //DEMO_TEXTURE2D_H
