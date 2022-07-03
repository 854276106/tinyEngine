//
// Created by zzn on 22-5-12.
//

#include "Texture2D.h"

Texture2D::Texture2D()
		: Slot(0),Internal_Format(GL_RGB), Image_Format(GL_RGB),
		  Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->TextureID);
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data, GLenum format)
{
	this->Internal_Format = format;
	// Create Texture
	//glActiveTexture(GL_TEXTURE0+Slot);  //激活纹理单元
	glBindTexture(GL_TEXTURE_2D, this->TextureID);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D,0, this->Internal_Format, width, height,
				0, this->Image_Format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->TextureID);
}
