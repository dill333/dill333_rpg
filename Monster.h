#pragma once

#include "Entity.h"

class Monster : public Entity
{
public:
	Monster(string shName, int tiX, int tiY);
	virtual void move();
	~Monster();
};

