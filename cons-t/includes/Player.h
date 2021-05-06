#pragma once

#include "Monster.h"

class Player {
private:
	int hpMax;
	int hp;
	int damage;

	void initVariables();

public:
	Player();
	virtual ~Player();

	const int& getDamage() const;
	const int& getHp() const;

	void setHp(const int value);
};
