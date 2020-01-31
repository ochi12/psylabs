#include <iostream>
#include <random>
#include <vector>
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
FpsCamera *cam;

glm::vec3 speed = glm::vec3(0);

std::vector<glm::vec3>* cubePos;

Game::Game() : r(new Renderer()){
	this->running = this->r->isValidState();

	Mesh* mesh = new Mesh(&cubeVertices[0][0], sizeof(cubeVertices),
			&cubeNormals[0][0], sizeof(cubeNormals),
			&cubeIndices[0][0], sizeof(cubeIndices), 36);
	Material* mat = new Material(glm::vec3(1, 1, 1), glm::vec3(1,1,1), glm::vec3(1,1,1), 64);

	m = new Model(mesh, mat);

	cam = new FpsCamera();
	m->mesh->bind();

	if (this->running) {
		std::default_random_engine rengine;
		std::uniform_int_distribution<int> uidist(-15, 15);
		std::uniform_real_distribution<float> urdist(0.0f, 1.0f);
		cubePos = new std::vector<glm::vec3>();
		for (int i = 0; i < 30; i++)
				cubePos->push_back(glm::vec3(uidist(rengine), uidist(rengine), uidist(rengine)));

		this->r->setPerspectiveProjection(30, 640.0f/480.0f, 0.01f, 1000);

		this->r->registerObject(m);

		this->r->setLightMask(31);
		for (int i = 0; i < 5; i++)
			this->r->setPointLight(i, PointLight(glm::vec3(uidist(rengine), uidist(rengine), uidist(rengine)), //pos
						glm::vec3(0.3f), // spec
						glm::vec3(0.7f, 0.2f, 0.2f), // diff
						glm::vec3(0.1f), // amb
						glm::vec3(1, 0.15, 0.075))); // att
	}
}

bool moving = false;
float movementDuration = 1, movementTime = 0;
glm::vec3 from(0), to(0);

void Game::update(float delta) {
	this->r->clearScreen();

	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
	glm::vec2 cameraRotation = glm::vec2(0, 0);

	int x, y;
	SDL_GetRelativeMouseState(&x, &y);

	float rotationSpeed = 90;
	cameraRotation = glm::vec2(-y, x) * rotationSpeed;
	cam->rotate(cameraRotation * delta);

	if (keyboard[SDL_SCANCODE_SPACE] && !moving) {
		from = cam->getPosition();

		// cast ray and move towards destination object
		// p and d are the passing point and direction of the ray
		glm::vec3 p = cam->getPosition();
		glm::vec3 d = cam->getForward();

		glm::vec3 res = glm::vec3(0);
		bool found = false;

		for (int i = 0; i < cubePos->size(); i++) {
			glm::vec3 pos = cubePos->at(i);

			glm::vec3 versors[] = {glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)};
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k <= 2; k += 2) {
					int s = k - 1;
					glm::vec3 dir = versors[j] * s;

					// c0 and n0 are the center and normal of the plane against which we'll be intersecting the ray
					glm::vec3 c0 = pos + (dir * 0.5f);
					glm::vec3 n0 = dir;

					// if the plane and the ray are not 'too' parallel
					float parallel = glm::dot(n0, d);
					if (glm::abs(parallel) > 0.0001f) {
						// find the parameter lambda which satisfies the equation of the plane
						float d0 = glm::dot(c0, n0), lambda;

						if (glm::abs(n0.x) > glm::abs(n0.y) && glm::abs(n0.x) > glm::abs(n0.z)) {
							lambda = (((d0/n0.x) - p.x) / d.x);
						} else if (glm::abs(n0.y) > glm::abs(n0.z)) {
							lambda = (((d0/n0.y) - p.y) / d.y);
						} else {
							lambda = (((d0/n0.z) - p.z) / d.z);
						}


						// check if the intersection occurs whithin the face's limits
						glm::vec3 intersectionPoint = p + (lambda * d);

						glm::vec3 projectedIntPoint = intersectionPoint * (glm::vec3(1, 1, 1) - (dir * s));
						glm::vec3 projectedPlaneCenter = c0 * (glm::vec3(1, 1, 1) - (dir * s));
						glm::vec3 diff = projectedIntPoint - projectedPlaneCenter;


						if (glm::abs(diff.x) < 0.5f && glm::abs(diff.y) < 0.5f && glm::abs(diff.z) < 0.5f) {
							if ((!found || (glm::length(p - intersectionPoint) < glm::length(p - res))) && lambda > 0) {
								found = true;
								res = intersectionPoint + (n0 * 0.1f);
							}
						}
					}
				}
				
			}
		}
		if (found) {
			to = res;
			movementDuration = glm::length(to - from) / 35;
			moving = true;
		}
	}

	if (moving) {
		movementTime += delta;
		if (movementTime >= movementDuration) {
			cam->getPosition() = to;
			moving = false;
			movementTime = 0;
		} else {
			glm::vec3 now = ((movementTime * (to - from)) / movementDuration) + from;
			cam->getPosition() = now;
		}
	}

	this->r->startRendering(cam);

	for (int i = 0; i < cubePos->size(); i++) {
		this->r->renderModel(m, cubePos->at(i));
	}

	this->r->endRendering();
}

bool Game::isRunning() {
	return this->running;
}

Game::~Game() {
	delete this->r;
	delete m;
	delete cubePos;
}
