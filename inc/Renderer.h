#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

#include "opengl.h"
#include "DefaultShader.h"
#include "Model.h"
#include "Camera.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void setPerspectiveProjection(float fovy, float aspect, float near, float far);

	void registerObject(Model* m);

	void clearScreen();
	void startRendering(Camera* m);

	void setRenderColor(glm::vec4 color);
	void renderModel(Model* m, glm::vec3 position, glm::vec3 scale);
	void renderModel(Model* m, glm::vec3 position);

	void endRendering();

	bool isValidState();
private:
	bool valid = true;
	DefaultShader* defaultShader = nullptr;
	Model* currentModel = nullptr;

	glm::mat4 projection = glm::identity<glm::mat4>();
};

#endif // _RENDERER_H_
