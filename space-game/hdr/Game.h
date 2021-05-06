#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game {
private:
  sf::RenderWindow* window;

  std::map<std::string,sf::Texture*> textures;
  std::vector<Bullet*> bullets;

  sf::Texture worldBgTex;
  sf::Sprite worldBgSpr;

  unsigned points;

  Player* player;

  sf::RectangleShape playerHpBar;
  sf::RectangleShape playerHpBarBack;

  float spawnTimer;
  float spawnTimerMax;
  std::vector<Enemy*> enemies;

  sf::Font font;
  sf::Text pointText;

  sf::Text gameOverText;

  void initWindow();
  void initTextures();
  void initGUI();
  void initWorld();
  void initSystems();

  void initPlayer();
  void initEnemies();
public:
  Game();
  virtual ~Game();

  void run();

  void updatePollEvents();
  void updateInput();
  void updateGUI();
  void updateWorld();
  void updateCollision();
  void updateBullets();
  void updateEnemies();
  void updateCombat();
  void update();
  void renderGUI();
  void renderWorld();
  void render();
};
