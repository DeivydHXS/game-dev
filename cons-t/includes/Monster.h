#pragma once

#include "Player.h"

class Monster {
private:
	int hpMax;
	int hp;
	int damage;

	void initVariables();

public:
	Monster();
	virtual ~Monster();

	const int& getDamage() const;
	const int& getHp() const;

	void setHp(const int value);

};
