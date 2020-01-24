#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

#include "opengl.h"
#include "DefaultShader.h"
#include "Model.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void setPerspectiveProjection(float fovy, float aspect, float near, float far);

	void rotateCamera(glm::vec3 rotation);
	void translateCamera(glm::vec3 translation);

	void registerObject(Model* m);

	void startRendering(Model* m);

	void setRenderColor(glm::vec4 color);
	void renderModel(glm::vec3 position, glm::vec3 scale);
	void renderModel(glm::vec3 position);

	void endRendering();

	bool isValidState();
private:
	bool valid = true;
	DefaultShader* defaultShader = nullptr;
	Model* currentModel = nullptr;

	glm::mat4 projection = glm::identity<glm::mat4>();
	glm::vec3 cameraPos = glm::vec3(0, 0, 0), cameraAngle = glm::vec3(0, 0, 0);
};

#endif // _RENDERER_H_
