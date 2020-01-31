#include "Renderer.h"
#include "resources.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "opengl.h"

Renderer::Renderer() {
	this->defaultShader = new DefaultShader();
	if (!this->defaultShader->isLinked()) {
		this->valid = false;
		return;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
	delete this->defaultShader;
}

void Renderer::setPerspectiveProjection(float fovy, float aspect, float near, float far) {
	this->defaultShader->bind();
	this->defaultShader->setPerspectiveProjectionMatrix(fovy, aspect, near, far);
	this->defaultShader->unbind();
}


void Renderer::registerObject(Model* m) {
	m->mesh->setAttributeIndices(this->defaultShader->getPosLocation(), this->defaultShader->getNormalLocation());
}

void Renderer::setPointLight(int i, const PointLight& l) {
	this->defaultShader->bind();
	this->defaultShader->setLight(i, l);
	this->defaultShader->unbind();
}

void Renderer::setLightMask(int i) {
	this->defaultShader->bind();
	this->defaultShader->setLightMask(i);
	this->defaultShader->unbind();
}

void Renderer::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::startRendering(FpsCamera* cam) {
	this->defaultShader->bind();

	glm::mat4 view = glm::identity<glm::mat4>();
	view = glm::rotate(view, glm::radians(-cam->getRotation().x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians( cam->getRotation().y), glm::vec3(0, 1, 0));

	view = glm::translate(view, glm::vec3(0, 0, 0) - cam->getPosition());
	this->defaultShader->setViewMatrix(view);
	this->defaultShader->setViewPos(cam->getPosition());
}

void Renderer::renderModel(Model* m, const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rotation) {
	if (m != this->currentModel) {
		if (this->currentModel != nullptr) {
			this->currentModel->mesh->unbind();
		}
		this->currentModel = m;
		this->currentModel->mesh->bind();
		this->defaultShader->setMaterial((*this->currentModel->material));
	}

	glm::mat4 model = glm::identity<glm::mat4>();
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	this->defaultShader->setModelMatrix(model);
	this->defaultShader->setNormalMatrix(glm::inverseTranspose(glm::mat3(model)));

	this->currentModel->mesh->draw();
}

void Renderer::renderModel(Model* m, const glm::vec3& pos, const glm::vec3& scale) {
	this->renderModel(m, pos, scale, glm::vec3(0, 0, 0));
}

void Renderer::renderModel(Model* m , const glm::vec3& pos) {
	this->renderModel(m, pos, glm::vec3(1, 1, 1));
}

void Renderer::endRendering() {
	this->defaultShader->unbind();
	this->currentModel->mesh->unbind();
	this->currentModel = nullptr;
}


bool Renderer::isValidState() {
	return this->valid;
}

