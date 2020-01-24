#ifndef _DEFAULT_SHADER_H_
#define _DEFAULT_SHADER_H_

#include "Shader.h"

class DefaultShader : public Shader {
public:
	DefaultShader();

	bool setPerspectiveProjection(float fovy, float aspect, float near, float far);
	bool setView(glm::mat4 view);
	bool setModel(glm::mat4 model);
	bool setColor(glm::vec4 color);

	inline GLuint getPosLocation() { return pos; };
	inline GLuint getNormalLocation() { return normal; };
private:
	const char* projection = "projection", *view = "view", *model = "model", *color = "color";
	const int pos = 0, normal = 1;
};

#endif // _DEFAULT_SHADER_H_
