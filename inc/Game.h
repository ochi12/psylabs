#ifndef _GAME_H_
#define _GAME_H_

#include "Renderer.h"

class Game {
public:
	Game();
	~Game();

	void update(float deltaTime);
	bool isRunning();
private:
	bool running = true;
	Renderer* r;
};

#endif //  _GAME_H_
