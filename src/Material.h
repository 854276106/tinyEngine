//
// Created by zzn on 22-5-13.
//

#ifndef DEMO_MATERIAL_H
#define DEMO_MATERIAL_H

#include <glm/glm.hpp>

class Material
{
public:
	Material(glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, float _shiness);
	~Material();
public:
	glm::vec3 ambient;
	unsigned int diffuse;
	unsigned int specular;
	float shiness;
};


#endif //DEMO_MATERIAL_H
