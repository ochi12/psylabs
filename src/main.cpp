#include <SDL2/SDL.h>

#include "Game.h"
#include "opengl.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

int main (int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL2 %s: ", SDL_GetError());
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s ", SDL_GetError());
		return -1;
	}

	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1) {
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Couldn't set relative mouse mode: %s\nYou might experience problems.", SDL_GetError());
	}

	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create OpenGL context: %s", SDL_GetError());
		return -1;
	}

	SDL_GL_SetSwapInterval(0);
	int swapInterval = SDL_GL_GetSwapInterval();
	if (swapInterval != 0) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Swap interval is %d, which differs from the desired interval(%d)", swapInterval, 0);
	}

	int minor, major, profile;
	int minorStatus = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	int majorStatus = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	int profileStatus = SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
	if (minorStatus != 0 || majorStatus != 0 || profileStatus != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get OpenGL context information: %s", SDL_GetError());
		return -1;
	} else {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Using OpenGL version %d.%d", major, minor);
		switch (profile) {
		case SDL_GL_CONTEXT_PROFILE_CORE:
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Using core profile");
			break;
		case SDL_GL_CONTEXT_PROFILE_COMPATIBILITY:
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Using compatibility profile");
			break;
		case SDL_GL_CONTEXT_PROFILE_ES:
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Using ES profile");
			break;
		}
	}

	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize GLEW: %s", glewGetErrorString(glewInitStatus));
		return -1;
	}
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Successfully initalized GLEW.");

	// We're good to go
	float dt = 0;
	int last = 0, now = 0;
	Game* game = new Game();
	bool running = game->isRunning();
	while (running) {
		now = SDL_GetTicks();
		dt = ((float)now - (float)last) / 1000.0f;
		last = now;

		if (SDL_QuitRequested() == SDL_TRUE) {
			running = false;
		}

		game->update(dt);
		running = running && game->isRunning();

		SDL_GL_SwapWindow(window);
	}
	delete game;

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	return 0;
}
