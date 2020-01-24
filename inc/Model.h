#ifndef _MODEL_H_
#define _MODEL_H_

#include <glm/glm.hpp>

#include "opengl.h"

class Model {
public:
	Model(GLfloat* mesh, GLsizeiptr meshSize, GLfloat* normals, GLsizeiptr normalsSize, GLuint* indices, GLsizeiptr indicesSize, GLuint triangles);
	~Model();

	void bind();
	void unbind();

	void setAttributeIndices(GLuint pos, GLuint normal);

	void draw();
private:
	GLuint vbo, ibo, vao, triangles;
	GLsizeiptr meshSize, normalsSize;
};

#endif // _MODEL_H_
