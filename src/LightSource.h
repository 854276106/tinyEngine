//
// Created by zzn on 22-5-13.
//

#ifndef DEMO_LIGHTSOURCE_H
#define DEMO_LIGHTSOURCE_H


#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

//平行光
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
			glm::vec3 _direction, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 direction;
	glm::vec3 color;
};

//点光源
class LightPoint
{
public:
	LightPoint(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _positon,
			float _constant, float _linear, float _quadratic, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();

public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
	glm::vec3 color;
	//衰减参数
	float constant;  //常数
	float linear;   //一次
	float quadratic;  //二次
};

//聚光
class LightSpot
{
public:
	LightSpot(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
			float _constant, float _linear, float _quadratic, float _cutOff, float _outerCutOff,
			glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	//衰减参数
	float constant;  //常数
	float linear;   //一次
	float quadratic;  //二次

	float cutOff;
	float outerCutOff;
public:
};


#endif //DEMO_LIGHTSOURCE_H
