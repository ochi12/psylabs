#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm/glm.hpp>

struct PointLight {
	PointLight(const glm::vec3& pos, const glm::vec3& spec, const glm::vec3& diff, const glm::vec3& amb, const glm::vec3& att) {
		this->position = pos;
		this->specular = spec;
		this->diffuse = diff;
		this->ambient = amb;
		this->attenuation = att;
	}

	glm::vec3 position, specular, diffuse, ambient, attenuation;
};

#endif // _LIGHT_H_
