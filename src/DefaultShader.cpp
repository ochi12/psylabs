#include <glm/ext.hpp>
#include <iostream>

#include "DefaultShader.h"
#include "resources.h"

DefaultShader::DefaultShader() : Shader(getResourcePath("default.vertex"), getResourcePath("default.fragment")) {
}

bool DefaultShader::setPerspectiveProjectionMatrix(float fovy, float aspect, float near, float far) {
	glm::mat4 proj = glm::perspective(glm::radians(fovy), aspect, near, far);
	return this->setUniform(this->projection, proj);
}

bool DefaultShader::setViewMatrix(const glm::mat4& view) {
	return this->setUniform(this->view, view);
}

bool DefaultShader::setModelMatrix(const glm::mat4& model) {
	return this->setUniform(this->model, model);
}

bool DefaultShader::setNormalMatrix(const glm::mat3& normal) {
	return this->setUniform(this->normalMatrix, normal);
}

bool DefaultShader::setMaterial(const Material& m) {
	bool success = true;
	success &= this->setUniform(this->matShine, m.shininess);
	success &= this->setUniform(this->matAmbient, m.ambient);
	success &= this->setUniform(this->matDiff, m.diffuse);
	success &= this->setUniform(this->matSpec, m.specular);
	return success;
}

bool DefaultShader::setLight(int i, const PointLight& l) {
	bool success = true;
	this->lightPos[7] = std::to_string(i)[0];
	this->lightAmbient[7] = std::to_string(i)[0];
	this->lightDiff[7] = std::to_string(i)[0];
	this->lightSpec[7] = std::to_string(i)[0];
	this->lightAtt[7] = std::to_string(i)[0];
	success &= this->setUniform(lightPos.c_str(), l.position);
	success &= this->setUniform(lightAmbient.c_str(), l.ambient);
	success &= this->setUniform(lightDiff.c_str(), l.diffuse);
	success &= this->setUniform(lightSpec.c_str(), l.specular);
	success &= this->setUniform(lightAtt.c_str(), l.attenuation);
	return success;
}

bool DefaultShader::setLightMask(int m) {
	return this->setUniform(this->lightMask, m);
}

bool DefaultShader::setViewPos(const glm::vec3& pos) {
	return this->setUniform(this->viewPos, pos);
}

