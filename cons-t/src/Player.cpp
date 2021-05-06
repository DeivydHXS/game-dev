#include "Player.h"

void Player::initVariables() {
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->hp = 5;
	this->damage = 5;
}

Player::Player() {
	this->initVariables();
}

Player::~Player() {

}

const int& Player::getDamage() const {
	return this->damage;
}

const int& Player::getHp() const {
	return this->hp;
}

void Player::setHp(const int value) {
	this->hp += value;
}
