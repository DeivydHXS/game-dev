#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float speed) {
  this->shape.setTexture(*texture);

  this->shape.setPosition(posX, posY);

  this->direction.x = dirX;
  this->direction.y = dirY;
  this->speed = speed;
}

Bullet::~Bullet() {

}

const sf::FloatRect Bullet::getBounds() const {
  return this->shape.getGlobalBounds();
}

void Bullet::update() {
  this->shape.move(this->speed * this->direction);
}

void Bullet::render(sf::RenderTarget& target) {
  target.draw(shape);
}
