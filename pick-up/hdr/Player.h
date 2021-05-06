#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Player {
private:
  sf::RectangleShape shape;

  float movementSpeed;
  int hp;
  int hpMax;

  void initVariables();
  void initShape();

public:
  Player(float x = 0, float y = 0);
  virtual ~Player();

  const sf::RectangleShape& getShape() const;
  const int& getHp() const;
  const int& getHpMax() const;

  void takeDamage(const int damage);
  void gainHealth(const int health);

  void updateInput();
  void updateWindowBoundsCollision(const sf::RenderTarget* target);
  void update(const sf::RenderTarget* target);
  void render(sf::RenderTarget* target);
};
