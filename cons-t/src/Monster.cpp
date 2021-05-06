#include "Monster.h"

void Monster::initVariables() {
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->hp = 5;
	this->damage = 3;
}

Monster::Monster() {
	this->initVariables();
}

Monster::~Monster() {

}

const int& Monster::getDamage() const {
	return this->damage;
}

const int& Monster::getHp() const {
	return this->hp;
}

void Monster::setHp(int value) {
	this->hp += value;
}
