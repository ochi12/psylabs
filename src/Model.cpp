#include "Model.h"

Model::Model(GLfloat* mesh, GLsizeiptr meshSize, GLfloat* normals, GLsizeiptr normalsSize, GLuint* indices, GLsizeiptr indicesSize, GLuint triangles) {
	glGenVertexArrays(1, &(this->vao));
	glBindVertexArray(this->vao);

	glGenBuffers(1, &(this->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glBufferData(GL_ARRAY_BUFFER, meshSize + normalsSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, meshSize, mesh);
	glBufferSubData(GL_ARRAY_BUFFER, meshSize, normalsSize, normals);


	glGenBuffers(1, &(this->ibo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->meshSize = meshSize;
	this->normalsSize = normalsSize;
	this->triangles = triangles;
}

Model::~Model() {
	glDeleteBuffers(1, &(this->vbo));
	glDeleteBuffers(1, &(this->ibo));

	glDeleteVertexArrays(1, &(this->vao));
}

void Model::bind() {
	glBindVertexArray(this->vao);
}

void Model::unbind() {
	glBindVertexArray(0);
}

void Model::setAttributeIndices(GLuint pos, GLuint normal) {
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindVertexArray(this->vao);

	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)meshSize);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::draw() {
	glDrawElements(GL_TRIANGLES, this->triangles, GL_UNSIGNED_INT, (void*)0);
}

