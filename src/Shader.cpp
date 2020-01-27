#include <SDL2/SDL.h>
#include <glm/ext.hpp>
#include <iostream>

#include "Shader.h"
#include "resources.h"

#define _DEBUG

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	this->uniformLocations = new std::map<std::string, GLint>();
	this->vertexAttributeLocations = new std::map<std::string, GLuint>();

	this->shaders = new ShaderInfo[3];
	this->shaders[0] = {GL_VERTEX_SHADER, vertexPath.c_str(), 0};
	this->shaders[1] = {GL_FRAGMENT_SHADER, fragmentPath.c_str(), 0};
	this->shaders[2] = {GL_NONE, "", 0};

	this->program = this->LoadShaders(shaders);
	if (this->program == 0) {
		this->linked = false;
		return;
	} else {
		this->linked = true;
	}
}

Shader::~Shader() {
	if (this->linked) {
		ShaderInfo* shader = this->shaders;
		while (shader->type != GL_NONE) {
			glDetachShader(this->program, shader->shader);
			glDeleteShader(shader->shader);
			++shader;
		}
		glDeleteProgram(this->program);
	}
	delete[] this->shaders;
	delete this->uniformLocations;
	delete this->vertexAttributeLocations;
}

void Shader::bind() {
	glUseProgram(this->program);
}

void Shader::unbind() {
	glUseProgram(0);
}

bool Shader::setUniform(std::string name, glm::mat4 value) {
	bool success = false;
	GLint loc = this->getUniformLocation(name);
	if (loc > -1) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
		success = true;
	}
	return success;
}

bool Shader::setUniform(std::string name, glm::mat3 value) {
	bool success = false;
	GLint loc = this->getUniformLocation(name);
	if (loc > -1) {
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
		success = true;
	}
	return success;
}


bool Shader::setUniform(std::string name, glm::vec4 value) {
	bool success = false;
	GLint loc = this->getUniformLocation(name);
	if (loc > -1) {
		glUniform4fv(loc, 1, glm::value_ptr(value));
		success = true;
	}
	return success;
}

bool Shader::setUniform(std::string name, glm::vec3 value) {
	bool success = false;
	GLint loc = this->getUniformLocation(name);
	if (loc > -1) {
		glUniform3fv(loc, 1, glm::value_ptr(value));
		success = true;
	}
	return success;
}

bool Shader::setUniform(std::string name, GLfloat value) {
	bool success = false;
	GLint loc = this->getUniformLocation(name);
	if (loc > -1) {
		glUniform1f(loc, value);
		success = true;
	}
	return success;
}

bool Shader::isLinked() {
	return this->linked;
}

GLint Shader::getUniformLocation(std::string name) {
	GLint loc = -1;
	if (this->uniformLocations->count(name) > 0) {
		loc = this->uniformLocations->at(name);
	} else {
		loc = glGetUniformLocation(this->program, name.c_str());
		if (loc > -1) {
			(*this->uniformLocations)[name] = loc;
		} else {
			std::cout << "holy moly" << name << std::endl;
		}
	}
	return loc;
}

const GLchar* Shader::ReadShader( const char* filename ) {
#ifdef WIN32
	FILE* infile;
	fopen_s( &infile, filename, "rb" );
#else
	FILE* infile = fopen( filename, "rb" );
#endif // WIN32

	if ( !infile ) {
#ifdef _DEBUG
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to open file '%s'", filename);
#endif /* DEBUG */
		return NULL;
	}
	
	fseek( infile, 0, SEEK_END );
	int len = ftell( infile );
	fseek( infile, 0, SEEK_SET );
	
	GLchar* source = new GLchar[len+1];
	
	fread( source, 1, len, infile );
	fclose( infile );
	
	source[len] = 0;
	
	return const_cast<const GLchar*>(source);
}

GLuint Shader::LoadShaders(ShaderInfo* shaders) {
	if ( shaders == NULL ) { return 0; }

	GLuint program = glCreateProgram();

	ShaderInfo* entry = shaders;
	while ( entry->type != GL_NONE ) {
		GLuint shader = glCreateShader( entry->type );

		entry->shader = shader;

		const GLchar* source = ReadShader( entry->filename );
		if ( source == NULL ) {
			for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
				glDeleteShader( entry->shader );
				entry->shader = 0;
			}

			return 0;
		}

		glShaderSource( shader, 1, &source, NULL );
		delete [] source;

		glCompileShader( shader );

		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled ) {
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetShaderInfoLog( shader, len, &len, log );
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader compilation failed: %s", log);
			delete [] log;
#endif /* DEBUG */
			return 0;
		}

		glAttachShader( program, shader );
		++entry;
	}
	
	glLinkProgram( program );
	
	GLint linked;
	glGetProgramiv( program, GL_LINK_STATUS, &linked );
	if ( !linked ) {
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
		
		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader linking failed: %s", log);
		delete [] log;
#endif /* DEBUG */
		for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
			glDeleteShader( entry->shader );
			entry->shader = 0;
		}
		
		return 0;
	}
	
	return program;
}

