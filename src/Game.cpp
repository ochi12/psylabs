#include "Game.h"
#include "opengl.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#define IMPORT_MODELS
#include "resources.h"

Model *m;
Camera *cam;

Game::Game() : r(new Renderer()){
	this->running = this->r->isValidState();
	m = new Model(&cubeVertices[0][0], sizeof(cubeVertices), &cubeNormals[0][0], sizeof(cubeNormals), &cubeIndices[0][0], sizeof(cubeIndices), 36);
	cam = new Camera();
	cam->getPosition() += glm::vec3(0, 0, 10);

	if (this->running) {
		this->r->setPerspectiveProjection(30, 640.0f/480.0f, 0.01f, 100);
		this->r->setRenderColor(glm::vec4(0, 0, 1, 1));

		this->r->registerObject(m);
	}
}

void Game::update(float delta) {
	this->r->clearScreen();
	this->r->startRendering(cam);

	this->r->renderModel(m, glm::vec3(0, 0,0), glm::vec3(1, 1, 1));

	this->r->endRendering();
}

bool Game::isRunning() {
	return this->running;
}

Game::~Game() {
	delete this->r;
	delete m;
}
