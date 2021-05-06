#include "Game.h"

void Game::initVariables() {
	this->isRunning = true;
}

Game::Game() {
	this->initVariables();
}

Game::~Game() {

}

void Game::clearScreen() {
	#ifdef WINDOWS
		std::system("cls");
	#else
		std::system("clear");
	#endif
}

void Game::run() {
	while (this->isRunning) {
		this->clearScreen();
		std::cout << "   Cons-t   " << '\n' << '\n'
							<< "1 - Explore" << '\n'
							<< "2 - Quit"     << '\n';

		int op;
		std::cin >> op;

		if (op == 1) {
			this->explore();
		} else if (op == 2) {
			std::cout << "Quit" << '\n';
			this->isRunning = false;
		}
	}
}

void Game::explore() {
	int num = rand()%10+1;

	if (num >= 5) {
		this->battle();
	} else if ( num < 5) {
		std::cout << "Nada foi encontrado." << '\n';
		sleep(1);
	}
}

void Game::battle() {
	std::cout << "Você encontrou um monstro." << '\n';
	bool battleRunning = true;

	while (battleRunning) {
		std::cout << "   Battle   "
							<< '\n'
							<< '\n'
							<< "Monster HP: "
							<< this->monster.getHp()
							<< '\n'
							<< "Player HP: "
							<< this->player.getHp()
							<< '\n'
							<< "1 - Attack" << '\n'
							<< "2 - Run"     << '\n';

		int battleOp;
		std::cin >> battleOp;

		if (battleOp == 1) {

			if (this->player.getHp() <= 0 || this->monster.getHp() <= 0) {
				battleRunning = false;
			} else {
				this->monster.setHp(-this->player.getDamage());
				sleep(1);
				this->player.setHp(-this->monster.getDamage());
			}

		} else if (battleOp == 2) {
			std::cout << "Running" << '\n';
			battleRunning = false;
		}
	}
}
