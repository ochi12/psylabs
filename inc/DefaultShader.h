#ifndef _DEFAULT_SHADER_H_
#define _DEFAULT_SHADER_H_

#include "Shader.h"
#include "Material.h"
#include "PointLight.h"

class DefaultShader : public Shader {
public:
	DefaultShader();

	bool setPerspectiveProjectionMatrix(float fovy, float aspect, float near, float far);
	bool setViewMatrix(const glm::mat4& view);
	bool setModelMatrix(const glm::mat4& model);
	bool setNormalMatrix(const glm::mat3& normal);

	bool setViewPos(const glm::vec3& pos);

	bool setMaterial(const Material& m);
	bool setLight(int i, const PointLight& l);
	bool setLightMask(int m);

	inline GLuint getPosLocation() { return pos; };
	inline GLuint getNormalLocation() { return normal; };
private:
	const char *projection = "projection", *view = "view", *model = "model", *normalMatrix="normalMatrix", *viewPos = "viewPos",
	      *matSpec = "material.specular", *matDiff = "material.diffuse", *matAmbient = "material.ambient", *matShine="material.shininess",
	      *lightMask = "lightMask";
	std::string  lightPos = "lights[0].position", lightSpec = "lights[0].specular", lightDiff = "lights[0].diffuse", lightAmbient = "lights[0].ambient",
	      lightAtt = "lights[0].attenuation";


	const int pos = 0, normal = 1;
};

#endif // _DEFAULT_SHADER_H_
