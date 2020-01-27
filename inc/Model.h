#ifndef _MODEL_H_
#define _MODEL_H_

#include <glm/glm.hpp>
#include <iostream>

#include "opengl.h"
#include "Mesh.h"
#include "Material.h"

struct Model {
	Model(Mesh* mesh, Material* mat) {
		this->mesh = mesh;
		this->material = mat;
	}

	~Model() {
		delete this->mesh;
		delete this->material;
	}

	Mesh *mesh;
	Material *material;
};

#endif // _MODEL_H_
