//
// Created by zzn on 22-5-13.
//

#include "LightSource.h"

LightDirectional::LightDirectional(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
		glm::vec3 _direction,glm::vec3 _color)
		: ambient(_ambient), diffuse(_diffuse), specular(_specular), direction(_direction), color(_color)
{

}

LightDirectional::~LightDirectional()
{

}

LightPoint::LightPoint(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _positon,
		float _constant,float _linear, float _quadratic, glm::vec3 _color)
		: ambient(_ambient), diffuse(_diffuse), specular(_specular), position(_positon),
		  constant(_constant), linear(_linear),quadratic(_quadratic), color(_color)
{

}

LightPoint::~LightPoint()
{

}

LightSpot::LightSpot(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear,
		float _quadratic, float _cutOff, float _outerCutOff, glm::vec3 _color)
		: ambient(_ambient), diffuse(_diffuse), specular(_specular),constant(_constant),
		linear(_linear), quadratic(_quadratic),cutOff(_cutOff), outerCutOff(_outerCutOff), color(_color)
{

}

LightSpot::~LightSpot()
{

}
