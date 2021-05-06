#include "Game.h"
#include "time.h"

int main() {
  // Init random seed
  srand(static_cast<unsigned>(time(0)));

  // Init game engine
  Game game;

  // Game loop
  game.run();

  // End of application
  return 0;
};
