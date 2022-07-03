//
// Created by zzn on 22-5-12.
//

#include <iostream>
#include "Shader.h"

Shader::Shader()
{

}

Shader& Shader::Use()
{
	glUseProgram(this->ShaderID);
	return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
	GLuint vertexShader,fragmentShader,geometryShader;

	vSource=vertexSource;
	fSource=fragmentSource;

	//vertexShader
	vertexShader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexSource, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader,"VERTEX");

	//fragmentShader
	fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader,"FRAGMENT");

	// If geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometrySource, NULL);
		glCompileShader(geometryShader);
		checkCompileErrors(geometryShader, "GEOMETRY");
	}

	//Shader Program
	this->ShaderID=glCreateProgram();
	glAttachShader(this->ShaderID,vertexShader);
	glAttachShader(this->ShaderID,fragmentShader);
	if (geometrySource != nullptr)
	{
		glAttachShader(this->ShaderID,geometryShader);
	}
	glLinkProgram(this->ShaderID);
	checkCompileErrors(this->ShaderID,"PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometrySource)
	{
		glDeleteShader(geometryShader);
	}
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform1f(glGetUniformLocation(this->ShaderID, name), value);
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform1i(glGetUniformLocation(this->ShaderID, name), value);
}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform2f(glGetUniformLocation(this->ShaderID, name), x, y);
}

void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform2f(glGetUniformLocation(this->ShaderID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform3f(glGetUniformLocation(this->ShaderID, name), x, y, z);
}

void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform3f(glGetUniformLocation(this->ShaderID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform4f(glGetUniformLocation(this->ShaderID, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform4f(glGetUniformLocation(this->ShaderID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->ShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- "
					  << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- "
					  << std::endl;
		}
	}
}
