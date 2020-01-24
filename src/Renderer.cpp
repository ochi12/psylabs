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
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
	delete this->defaultShader;
}

void Renderer::setPerspectiveProjection(float fovy, float aspect, float near, float far) {
	this->defaultShader->bind();
	this->defaultShader->setPerspectiveProjection(fovy, aspect, near, far);
	this->defaultShader->unbind();
}


void Renderer::registerObject(Model* m) {
	m->setAttributeIndices(this->defaultShader->getPosLocation(), this->defaultShader->getNormalLocation());
}

void Renderer::setLight(glm::vec3 pos, glm::vec4 color, float intensity) {
	this->defaultShader->bind();
	this->defaultShader->setLightPos(pos);
	this->defaultShader->setLightColor(color);
	this->defaultShader->setLightIntensity(intensity);
	this->defaultShader->unbind();
}

void Renderer::setAmbientLight(glm::vec4 color, float intensity) {
	this->defaultShader->bind();
	this->defaultShader->setAmbientLightColor(color);
	this->defaultShader->setAmbientLightIntensity(intensity);
	this->defaultShader->unbind();
}

void Renderer::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::startRendering(Camera* cam) {
	this->defaultShader->bind();

	glm::mat4 view = glm::identity<glm::mat4>();
	view = glm::rotate(view, glm::radians(-cam->getRotation().x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians(-cam->getRotation().y), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(-cam->getRotation().z), glm::vec3(0, 0, 1));

	view = glm::translate(view, glm::vec3(0, 0, 0) - cam->getPosition());
	this->defaultShader->setView(view);
}

void Renderer::renderModel(Model* m, glm::vec3 pos, glm::vec3 scale) {
	if (m != this->currentModel) {
		this->currentModel->unbind();
		this->currentModel = m;
		this->currentModel->bind();
	}

	glm::mat4 model = glm::identity<glm::mat4>();
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);

	this->defaultShader->setModel(model);

	this->currentModel->draw();
}

void Renderer::renderModel(Model* m ,glm::vec3 pos) {
	this->renderModel(m, pos, glm::vec3(1, 1, 1));
}

void Renderer::endRendering() {
	this->defaultShader->unbind();
	this->currentModel->unbind();
	this->currentModel = nullptr;
}

void Renderer::setRenderColor(glm::vec4 color) {
	this->defaultShader->bind();
	this->defaultShader->setColor(color);
	this->defaultShader->unbind();
}

bool Renderer::isValidState() {
	return this->valid;
}

