#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
private:
  unsigned pointCount;
  sf::CircleShape shape;
  int type;
  float speed;
  int hp;
  int hpMax;
  int damage;
  int points;

  void initVariables();
  void initShape();
public:
  Enemy(float posX, float posY);
  virtual ~Enemy();

  const sf::FloatRect getBounds() const;
  const int& getPoints() const;
  const int& getDamage() const;

  void update();
  void render(sf::RenderTarget* target);
};
