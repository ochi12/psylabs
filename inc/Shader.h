#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <map>
#include <glm/glm.hpp>

#include "opengl.h"

class Shader {
public:
	~Shader();

	void bind();
	void unbind();

	bool isLinked();
protected:
	Shader(std::string vertexPath, std::string fragmentPath);

	bool setUniform(std::string, glm::mat4 value);
	bool setUniform(std::string, glm::mat3 value);
	bool setUniform(std::string, glm::vec4 value);
	bool setUniform(std::string, glm::vec3 value);
	bool setUniform(std::string, GLfloat value);
	bool setUniform(std::string, GLint value);
private:
	typedef struct {
	    GLenum       type;
	    const char*  filename;
	    GLuint       shader;
	} ShaderInfo;

	std::map<std::string, GLint>* uniformLocations;
	std::map<std::string, GLuint>* vertexAttributeLocations;

	GLuint program;
	ShaderInfo* shaders;
	bool linked;

	GLint getUniformLocation(std::string name);
	GLuint LoadShaders(ShaderInfo*);
	const GLchar* ReadShader( const char* filename );
};

#endif // _SHADER_H_

