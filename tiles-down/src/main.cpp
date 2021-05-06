#include "Game.h"

int main() {
  // Init srand
  std::srand(static_cast<unsigned>(time(NULL)));

  // Init game engine
  Game game;

  // Game loop
  while (game.running() && !game.getEndGame()) {

    // UPDATE
    game.update();

    // RENDER
    game.render();
  }

  // End of application
  return 0;
};
