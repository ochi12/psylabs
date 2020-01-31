#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class FpsCamera {
public:
	FpsCamera();
	~FpsCamera();

	const glm::vec3& getForward();
	const glm::vec3& getUp();
	const glm::vec2& getRotation();
	glm::vec3 getRight();

	void rotate(glm::vec2 rotation);
	void setRotation(glm::vec3 rotation);

	glm::vec3& getPosition();
private:
	void rotationUpdated();
	glm::vec3 *forward, *pos, *up;
	glm::vec2 *rotation;
};

#endif // _CAMERA_H_
