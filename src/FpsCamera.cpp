#include "FpsCamera.h"

glm::vec3 getVector(float alpha, float beta) {
	float r = cos(glm::radians(alpha)) * (glm::abs(alpha) == 90 ? -1 : 1);

	return glm::vec3(
		 sin(glm::radians(beta)) * r,
		 sin(glm::radians(alpha)),
		-cos(glm::radians(beta)) * r);
}

FpsCamera::FpsCamera() {
	this->forward = new glm::vec3(0, 0, -1);
	this->up = new glm::vec3(0, 1, 0);
	this->rotation = new glm::vec2(0, 0);
	this->pos = new glm::vec3(0, 0, 0);
}

FpsCamera::~FpsCamera() {
	delete this->forward;
	delete this->up;
	delete this->rotation;
	delete this->pos;
}

const glm::vec3& FpsCamera::getForward() {
	return (*this->forward);
}

const glm::vec3& FpsCamera::getUp() {
	return (*this->up);
}

const glm::vec2& FpsCamera::getRotation() {
	return (*this->rotation);
}

glm::vec3 FpsCamera::getRight() {
	return -glm::normalize(glm::cross(this->getUp(), this->getForward()));
}

void FpsCamera::rotate(glm::vec2 rotation) {
	(*this->rotation) += rotation;
	this->rotationUpdated();
}

void FpsCamera::setRotation(glm::vec3 rotation) {
	(*this->rotation) = rotation;
	this->rotationUpdated();
}

glm::vec3& FpsCamera::getPosition() {
	return (*this->pos);
}

void FpsCamera::rotationUpdated() {
	if(glm::abs(this->rotation->x) > 90) {
		this->rotation->x = 90 * glm::sign(this->rotation->x);
	}
	(*this->forward) = getVector(this->rotation->x, this->rotation->y);
}
