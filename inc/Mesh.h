#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>

#include "opengl.h"

class Mesh {
public:
	Mesh(GLfloat* mesh, GLsizeiptr meshSize, GLfloat* normals, GLsizeiptr normalsSize, GLuint* indices, GLsizeiptr indicesSize, GLuint triangles);
	~Mesh();

	void bind();
	void unbind();

	void setAttributeIndices(GLuint pos, GLuint normal);

	void draw();
private:
	GLuint vbo, ibo, vao, triangles;
	GLsizeiptr meshSize, normalsSize;
};

#endif // _MESH_H_
