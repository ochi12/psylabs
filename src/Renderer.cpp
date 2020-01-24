#include "Renderer.h"
#include "resources.h"
#include "opengl.h"

Renderer::Renderer() {
	this->defaultShader = new DefaultShader();
	if (!this->defaultShader->isLinked()) {
		this->valid = false;
		return;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Renderer::~Renderer() {
	delete this->defaultShader;
}

void Renderer::setPerspectiveProjection(float fovy, float aspect, float near, float far) {
	this->defaultShader->bind();
	this->defaultShader->setPerspectiveProjection(fovy, aspect, near, far);
	this->defaultShader->unbind();
}

void Renderer::rotateCamera(glm::vec3 rotation) {
	this->cameraAngle -= rotation;
}

void Renderer::translateCamera(glm::vec3 translation) {
	this->cameraPos -= translation;
}

void Renderer::registerObject(Model* m) {
	m->setAttributeIndices(this->defaultShader->getPosLocation(), this->defaultShader->getNormalLocation());
}

void Renderer::startRendering(Model* m) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->currentModel = m;
	this->currentModel->bind();
	this->defaultShader->bind();

	glm::mat4 view = glm::identity<glm::mat4>();
	view = glm::rotate(view, this->cameraAngle.x, glm::vec3(1, 0, 0));
	view = glm::rotate(view, this->cameraAngle.y, glm::vec3(0, 1, 0));
	view = glm::rotate(view, this->cameraAngle.z, glm::vec3(0, 0, 1));

	view = glm::translate(view, this->cameraPos);

	this->defaultShader->setView(view);
}

void Renderer::renderModel(glm::vec3 pos, glm::vec3 scale) {
	glm::mat4 model = glm::identity<glm::mat4>();
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);

	this->defaultShader->setModel(model);

	this->currentModel->draw();
}

void Renderer::renderModel(glm::vec3 pos) {
	this->renderModel(pos, glm::vec3(1, 1, 1));
}

void Renderer::endRendering() {
	this->defaultShader->unbind();
	this->currentModel->unbind();
}

void Renderer::setRenderColor(glm::vec4 color) {
	this->defaultShader->setColor(color);
}

bool Renderer::isValidState() {
	return this->valid;
}

