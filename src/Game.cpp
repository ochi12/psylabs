#include <iostream>
#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Game.h"
#include "opengl.h"


#define IMPORT_MODELS
#include "resources.h"

Model *m;
Camera *cam;

Game::Game() : r(new Renderer()){
	this->running = this->r->isValidState();
	m = new Model(&cubeVertices[0][0], sizeof(cubeVertices), &cubeNormals[0][0], sizeof(cubeNormals), &cubeIndices[0][0], sizeof(cubeIndices), 36);
	cam = new Camera();

	if (this->running) {
		this->r->setPerspectiveProjection(30, 640.0f/480.0f, 0.01f, 1000);
		this->r->setRenderColor(glm::vec4(1, 1, 1, 1));

		this->r->registerObject(m);

		this->r->setLight(glm::vec3(0, 0, 0), glm::vec4(0.3f, 0.3f, 1, 1), 25);
		this->r->setAmbientLight(glm::vec4(1, 0, 0, 1), 0.2f);
	}
}

void Game::update(float delta) {
	this->r->clearScreen();

	bool rotated = false;
	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
	glm::vec3 cameraRotation = glm::vec3(0, 0, 0);

	int x, y;
	SDL_GetRelativeMouseState(&x, &y);

	float rotationSpeed = 45;
	cameraRotation = glm::vec3(-y * rotationSpeed, -x * rotationSpeed, 0);
	cam->rotate(cameraRotation * delta);

	float movementSpeed = 20;
	glm::vec3 cameraMovement = glm::vec3(0, 0, 0);
	if (keyboard[SDL_SCANCODE_SPACE]) {
		cameraMovement += cam->getUp() / 2;
	} if (keyboard[SDL_SCANCODE_LSHIFT]) {
		cameraMovement -= cam->getUp() / 2;
	} if (keyboard[SDL_SCANCODE_W]) {
		cameraMovement += cam->getForward();
	} if (keyboard[SDL_SCANCODE_S]) {
		cameraMovement -= cam->getForward();
	} if (keyboard[SDL_SCANCODE_D]) {
		cameraMovement += cam->getRight();
	} if (keyboard[SDL_SCANCODE_A]) {
		cameraMovement -= cam->getRight();
	}

	cameraMovement *= movementSpeed;

	cam->getPosition() += (cameraMovement * delta);

	this->r->startRendering(cam);

	for (int i = -10; i < 10; i++)
		for (int j = -10; j < 10; j++)
			for (int k = -10; k < 10; k++)
				if (i != 0 || j != 0 || k != 0)
					this->r->renderModel(m, glm::vec3(i * 7, j * 7, k * 7), glm::vec3(1, 1, 1));

	this->r->endRendering();
}

bool Game::isRunning() {
	return this->running;
}

Game::~Game() {
	delete this->r;
	delete m;
}
