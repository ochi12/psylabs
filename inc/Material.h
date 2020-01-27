#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <glm/glm.hpp>

struct Material {
	Material(const glm::vec3& diff, const glm::vec3& ambient, const glm::vec3& specular, float shininess) {
		this->diffuse = diff;
		this->ambient = ambient;
		this->specular = specular;
		this->shininess = shininess;
	}

	glm::vec3 diffuse, ambient, specular;
	float shininess;
};

#endif // _MATERIAL_H_
