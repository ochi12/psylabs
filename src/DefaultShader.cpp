#include <glm/ext.hpp>

#include "DefaultShader.h"
#include "resources.h"

DefaultShader::DefaultShader() : Shader(getResourcePath("default.vertex"), getResourcePath("default.fragment")) {
}

bool DefaultShader::setPerspectiveProjection(float fovy, float aspect, float near, float far) {
	glm::mat4 proj = glm::perspective(glm::radians(fovy), aspect, near, far);
	return this->setUniform(this->projection, proj);
}

bool DefaultShader::setView(glm::mat4 view) {
	return this->setUniform(this->view, view);
}

bool DefaultShader::setModel(glm::mat4 model) {
	return this->setUniform(this->model, model);
}

bool DefaultShader::setColor(glm::vec4 color) {
	return this->setUniform(this->color, color);
}

bool DefaultShader::setLightPos(glm::vec3 pos) {
	return this->setUniform(this->lightPos, pos);
}

bool DefaultShader::setLightIntensity(float intensity) {
	return this->setUniform(this->lightIntensity, intensity);
}

bool DefaultShader::setLightColor(glm::vec4 color) {
	return this->setUniform(this->lightColor, color);
}

bool DefaultShader::setAmbientLightColor(glm::vec4 color) {
	return this->setUniform(this->ambientLightColor, color);
}

bool DefaultShader::setAmbientLightIntensity(float intensity) {
	return this->setUniform(this->ambientLightIntensity, intensity);
}
