#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Player.h"
#include "SwagBall.h"

class Game {
private:
  sf::RenderWindow* window;
  sf::VideoMode videoMode;
  sf::Event ev;
  bool endGame;

  Player player;

  int points;

  sf::Font font;
  sf::Text guiText;
  sf::Text endGameText;

  std::vector<SwagBall> swagBalls;
  float spawnTimerMax;
  float spawnTimer;
  int maxSwagBalls;

  void initVariables();
  void initWindow();
  void initFont();
  void initText();
public:
  Game();
  virtual ~Game();

  const bool& getEndGame() const;

  const bool isRunning() const;
  void pollEvents();

  void spawnSwagBalls();
  const int randBallType();
  void updatePlayer();
  void updateCollision();
  void updateGUI();
  void update();

  void renderGUI(sf::RenderTarget* target);
  void render();
};
