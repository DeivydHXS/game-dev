#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum SwagBallTypes {
  DEFAULT = 0,
  DAMAGING,
  HEALING,
  NROFTYPES
};

class SwagBall {
private:
  sf::CircleShape shape;
  int type;

  float movementSpeed;

  void initShape(const sf::RenderTarget& window);

public:
  SwagBall(const sf::RenderTarget& window, int type);
  virtual ~SwagBall();

  const sf::CircleShape& getShape() const;
  const int& getType() const;

  void update();
  void render(sf::RenderTarget& target);
};
