#ifndef _DEFAULT_SHADER_H_
#define _DEFAULT_SHADER_H_

#include "Shader.h"

class DefaultShader : public Shader {
public:
	DefaultShader();

	bool setPerspectiveProjection(float fovy, float aspect, float near, float far);
	bool setView(glm::mat4 view);
	bool setModel(glm::mat4 model);
	bool setNormalMatrix(glm::mat3 normal);
	bool setColor(glm::vec4 color);

	bool setLightPos(glm::vec3 pos);
	bool setLightColor(glm::vec4 color);
	bool setLightIntensity(float intensity);

	bool setAmbientLightColor(glm::vec4 color);
	bool setAmbientLightIntensity(float intensity);

	bool setShininess(float shininess);
	bool setSpecularIntensity(float shininess);

	bool setViewPos(glm::vec3 pos);

	inline GLuint getPosLocation() { return pos; };
	inline GLuint getNormalLocation() { return normal; };
private:
	const char* projection = "projection", *view = "view", *model = "model", *normalMatrix="normalMatrix",
	      *color = "color", 
	      *lightPos = "lightPos", *lightIntensity = "lightIntensity", *lightColor = "lightColor", 
	      *ambientLightColor = "ambientColor", *ambientLightIntensity = "ambientIntensity",
	      *viewPos = "viewPos", *shininess="shininess", *specularIntensity = "specularIntensity";

	const int pos = 0, normal = 1;
};

#endif // _DEFAULT_SHADER_H_
