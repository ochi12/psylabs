#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

#include "opengl.h"
#include "DefaultShader.h"
#include "Model.h"
#include "FpsCamera.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void setPerspectiveProjection(float fovy, float aspect, float near, float far);

	void registerObject(Model* m);
	void setPointLight(int i, const PointLight& l);
	void setLightMask(int i);

	void clearScreen();
	void startRendering(FpsCamera* m);

	void renderModel(Model* m, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);
	void renderModel(Model* m, const glm::vec3& position, const glm::vec3& scale);
	void renderModel(Model* m, const glm::vec3& position);

	void endRendering();

	bool isValidState();
private:
	bool valid = true;
	DefaultShader* defaultShader = nullptr;
	Model* currentModel = nullptr;
};

#endif // _RENDERER_H_
