#include "SwagBall.h"

void SwagBall::initShape(const sf::RenderTarget& window) {
  this->shape.setRadius(static_cast<float>(rand()%10+10));
  sf::Color color;
  switch (this->type) {
    case SwagBallTypes::DEFAULT:
      color = sf::Color(rand()%255+1,rand()%255+1,255);
      break;
    case SwagBallTypes::DAMAGING:
      color = sf::Color(255,rand()%255+1,rand()%255+1);
      break;
    case SwagBallTypes::HEALING:
      color = sf::Color(rand()%255+1,255,rand()%255+1);
      break;
  }
  this->shape.setFillColor(color);
  this->shape.setPosition(
    sf::Vector2f(
      static_cast<float>(rand()%window.getSize().x - this->shape.getGlobalBounds().width),
      static_cast<float>(rand()%window.getSize().y - this->shape.getGlobalBounds().height)
    )
  );
}

SwagBall::SwagBall(const sf::RenderTarget& window, int type) : type(type) {
  this->initShape(window);
}

SwagBall::~SwagBall() {

}

const sf::CircleShape& SwagBall::getShape() const {
  return this->shape;
}

const int& SwagBall::getType() const {
  return this->type;
}

void SwagBall::update() {

}

void SwagBall::render(sf::RenderTarget& target) {
  target.draw(this->shape);
}
