#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#include "Player.h"
#include "Monster.h"

class Game {
private:

	bool isRunning;

	Player player;
	Monster monster;

	void initVariables();

public:
	Game();
	virtual ~Game();

	void clearScreen();
	void run();
	void explore();
	void battle();
};
