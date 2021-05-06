#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Player {
private:
  sf::Sprite sprite;
  sf::Texture texture;

  float speed;

  float attackCooldown;
  float attackCooldownMax;

  int hpMax;
  int hp;

  void initVariables();
  void initTexture();
  void initSprite();
public:
  Player();
  virtual ~Player();

  const sf::Vector2f& getPos() const;
  const sf::FloatRect getBounds() const;
  const int& getHp() const;
  const int& getHpMax() const;

  void setPosition(const sf::Vector2f pos);
  void setPosition(const float x, const float y);
  void setHp(const int hp);
  void loseHp(const int value);

  void move(const float dirX,const float dirY);
  const bool canAttack();

  void updateAttack();
  void update();
  void render(sf::RenderTarget& target);
};
