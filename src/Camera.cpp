#include "Camera.h"

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

const glm::vec3* Camera::getForward() {
	return this->forward;
}

const glm::vec3* Camera::getUp() {
	return this->up;
}

const glm::vec3* Camera::getRotation() {
	return this->rotation;
}

void Camera::rotate(glm::vec3 rotation) {
	(*this->rotation) += rotation;
	float alpha = rotation.y;
	float theta = rotation.x;
	float r = cos(glm::radians(theta));

	this->forward->x = sin(glm::radians(alpha)) * r;
	this->forward->y = sin(glm::radians(theta));
	this->forward->z = cos(glm::radians(alpha)) * r;

	this->up->x = 0;
	this->up->y = 1;
	this->up->z = 0;
}

void Camera::setRotation(glm::vec3 rotation) {
	this->rotation->x = 0;
	this->rotation->y = 0;
	this->rotation->z = 0;

	this->forward->x = 0;
	this->forward->y = 0;
	this->forward->z = -1;

	this->up->x = 0;
	this->up->y = 1;
	this->up->z = 0;

	this->rotate(rotation);
}

glm::vec3& Camera::getPosition() {
	return (*this->pos);
}
