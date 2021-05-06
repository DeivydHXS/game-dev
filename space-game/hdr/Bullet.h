#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>


class Bullet {
private:
  sf::Sprite shape;

  sf::Vector2f direction;
  float speed;

  void initTexture();
  void initSprite();
public:
  Bullet(sf::Texture* texture, float posX, float PosY, float dirX, float dirY, float speed);
  virtual ~Bullet();

  const sf::FloatRect getBounds() const;

  void update();
  void render(sf::RenderTarget& target);
};
