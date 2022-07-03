//
// Created by zzn on 22-5-13.
//

#include "Material.h"

Material::Material(glm::vec3 _ambient, unsigned int _diffues, unsigned int _specular, float _shiness)
		:ambient(_ambient), diffues(_diffues), specular(_specular), shiness(_shiness)
{

}

Material::~Material()
{

}
