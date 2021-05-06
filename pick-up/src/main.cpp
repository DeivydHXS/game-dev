#include "Game.h"

int main() {
  // Init random seed
  std::srand(static_cast<unsigned>(time(0)));

  // Init game engine
  Game game;

  // Game loop
  while (game.isRunning()) {

    // UPDATE
    game.update();

    // RENDER
    game.render();
  }

  // End of application
  return 0;
};
