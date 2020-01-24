#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <string>

#include "opengl.h"

std::string getResourcePath(std::string filename);


#ifdef IMPORT_MODELS
GLfloat cubeVertices[24][3] = {
	// Upper face
	{-0.5f,  0.5f, -0.5f},
	{-0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f, -0.5f},
	// Right face        ,
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	// Bottom face       ,
	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},
	// Left face         ,
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	// Front face        ,
	{-0.5f,  0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	// Back face         ,
	{-0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f}
};

GLfloat cubeNormals[24][3] = {
	// Upper face
	{0.0f,  1.0f,  0.0f},
  	{0.0f,  1.0f,  0.0f},
  	{0.0f,  1.0f,  0.0f},
  	{0.0f,  1.0f,  0.0f},
	// Right face
  	{1.0f,  0.0f,  0.0f},
  	{1.0f,  0.0f,  0.0f},
  	{1.0f,  0.0f,  0.0f},
  	{1.0f,  0.0f,  0.0f},
	// Bottom face
  	{0.0f, -1.0f,  0.0f},
  	{0.0f, -1.0f,  0.0f},
  	{0.0f, -1.0f,  0.0f},
  	{0.0f, -1.0f,  0.0f},
	// Left face
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	// Front face
  	{0.0f,  0.0f,  1.0f},
  	{0.0f,  0.0f,  1.0f},
  	{0.0f,  0.0f,  1.0f},
  	{0.0f,  0.0f,  1.0f},
	// Back face
  	{0.0f,  0.0f, -1.0f},
  	{0.0f,  0.0f, -1.0f},
  	{0.0f,  0.0f, -1.0f},
  	{0.0f,  0.0f, -1.0f}
};	

GLuint cubeIndices[6][6] = {
	// Upper face
	{0, 1, 2, 2, 3, 0},
	// Right face
	{4, 5, 6, 6, 7, 4},
	// Bottom face
	{8, 9, 10, 10, 11, 8},
	// Left face
	{12, 13, 14, 14, 15, 12},
	// Front face
	{16, 17, 18, 18, 19, 16},
	// Back face
	{20, 21, 22, 22, 23, 20}
};

#endif // IMPORT_MODELS

#endif // _RESOURCES_H_
