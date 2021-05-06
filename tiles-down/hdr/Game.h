#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
  Class that acts as the game engine.
  Wrapper class.
*/

#ifndef GAME_H
#define GAME_H

class Game {
private:
  // Variables
  //Window
  sf::RenderWindow* window;
  sf::VideoMode videoMode;
  sf::Event ev;

  // Mouse position
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;

  // Resources
  sf::Font font;

  // Text
  sf::Text uiText;

  // Game logic
  bool endGame;
  unsigned points;
  int health;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;
  bool mouseHeld;

  // Game objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;

  // Private functions
  void initVariables();
  void initWindow();
  void initFonts();
  void initText();
  void initEnemies();
public:
  // Constructor and Destructor
  Game();
  virtual ~Game();

  // Accesors
  const bool running() const;
  const bool getEndGame() const;

  // Functions
  void spawnEnemy();

  void pollEvents();
  void updateMousePosition();

  void updateText();
  void updateEnemies();
  void update();

  void renderText(sf::RenderTarget& target);
  void renderEnemies(sf::RenderTarget& target);
  void render();
};

#endif