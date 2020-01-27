#include "Camera.h"

glm::vec3 getVector(float alpha, float beta) {
	float r = cos(glm::radians(alpha));

	return glm::vec3(
		 sin(glm::radians(beta)) * r,
		 sin(glm::radians(alpha)),
		-cos(glm::radians(beta)) * r);
}

Camera::Camera() {
	this->forward = new glm::vec3(0, 0, -1);
	this->up = new glm::vec3(0, 1, 0);
	this->rotation = new glm::vec3(0, 0, 0);
	this->pos = new glm::vec3(0, 0, 0);
}

Camera::~Camera() {
	delete this->forward;
	delete this->up;
	delete this->rotation;
	delete this->pos;
}

const glm::vec3& Camera::getForward() {
	return (*this->forward);
}

const glm::vec3& Camera::getUp() {
	return (*this->up);
}

const glm::vec3& Camera::getRotation() {
	return (*this->rotation);
}

glm::vec3 Camera::getRight() {
	return -glm::normalize(glm::cross(this->getUp(), this->getForward()));
}

void Camera::rotate(glm::vec3 rotation) {
	(*this->rotation) += rotation;
	this->rotationUpdated();
}

void Camera::setRotation(glm::vec3 rotation) {
	(*this->rotation) = rotation;

	this->rotationUpdated();
}

glm::vec3& Camera::getPosition() {
	return (*this->pos);
}

void Camera::rotationUpdated() {
	(*this->forward) = getVector(this->rotation->x, this->rotation->y);
	(*this->up) = getVector(this->rotation->x + 90, this->rotation->y);
}
