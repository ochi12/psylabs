#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	~Camera();

	const glm::vec3* getForward();
	const glm::vec3* getUp();
	const glm::vec3* getRotation();

	void rotate(glm::vec3 rotation);
	void setRotation(glm::vec3 rotation);

	glm::vec3& getPosition();
private:
	glm::vec3 *forward, *pos, *up, *rotation;
};

#endif // _CAMERA_H_
