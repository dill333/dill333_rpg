#pragma once

#include "Entity.h"

class Player : public Entity
{
	bool canAttack;
public:
	Player();
	Player(string shName, int tiX, int tiY);
	virtual void move();
	~Player();
};

