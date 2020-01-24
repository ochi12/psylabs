#include "Game.h"
#include "opengl.h"

#define IMPORT_MODELS
#include "resources.h"

Model* m;

Game::Game() : r(new Renderer()){
	this->running = this->r->isValidState();
	m = new Model(&cubeVertices[0][0], sizeof(cubeVertices), &cubeNormals[0][0], sizeof(cubeNormals), &cubeIndices[0][0], sizeof(cubeIndices), 36);

	if (this->running) {
		this->r->setPerspectiveProjection(30, 640.0f/480.0f, 0.01f, 100);
		this->r->translateCamera(glm::vec3(0, 0, 10));

		this->r->registerObject(m);
	}
}

void Game::update(float delta) {
	this->r->startRendering(m);

	this->r->rotateCamera(glm::vec3(0.1f, 0.1f, 0.1f) * delta);
	this->r->setRenderColor(glm::vec4(0, 0, 1, 1));
	this->r->renderModel(glm::vec3(0, 0,0), glm::vec3(1, 1, 1));

	this->r->endRendering();
}

bool Game::isRunning() {
	return this->running;
}

Game::~Game() {
	delete this->r;
	delete m;
}
