#include <iostream>
#include <SDL2/SDL.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Game.h"
#include "Mesh.h"
#include "Material.h"
#include "opengl.h"


#define IMPORT_MODELS
#include "resources.h"

Model *m;
Camera *cam;

Game::Game() : r(new Renderer()){
	this->running = this->r->isValidState();

	Mesh* mesh = new Mesh(&cubeVertices[0][0], sizeof(cubeVertices),
			&cubeNormals[0][0], sizeof(cubeNormals),
			&cubeIndices[0][0], sizeof(cubeIndices), 36);
	Material* mat = new Material(glm::vec3(1, 1, 1), glm::vec3(1,1,1), glm::vec3(1,1,1), 64);

	m = new Model(mesh, mat);

	cam = new Camera();
	m->mesh->bind();

	if (this->running) {
		this->r->setPerspectiveProjection(30, 640.0f/480.0f, 0.01f, 1000);

		this->r->registerObject(m);

		this->r->setLightMask(3);
		this->r->setPointLight(0, PointLight(glm::vec3(-25, -25, -25), glm::vec3(0.4f), glm::vec3(1), glm::vec3(0.1f), glm::vec3(1, 0.014f, 0.0074f)));
		this->r->setPointLight(1, PointLight(glm::vec3( 25,  25,  25), glm::vec3(0.4f), glm::vec3(1), glm::vec3(0.1f), glm::vec3(1, 0.014f, 0.0074f)));
	}
}

void Game::update(float delta) {
	this->r->clearScreen();

	bool rotated = false;
	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
	glm::vec3 cameraRotation = glm::vec3(0, 0, 0);

	int x, y, z = 0;
	SDL_GetRelativeMouseState(&x, &y);

	float rotationSpeed = 20;
	cameraRotation = glm::vec3(-y, x, z) * rotationSpeed;
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

	for (int i = -5; i <= 5; i++)
		for (int j = -5; j <= 5; j++)
			for (int k = -5; k <= 5; k++)
				if (i != 0 || j != 0 || k != 0)
					this->r->renderModel(m, glm::vec3(i * 5, j * 5, k * 5));

	this->r->endRendering();
}

bool Game::isRunning() {
	return this->running;
}

Game::~Game() {
	delete this->r;
	delete m;
}
