#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
	void move();
public:
	Player();
	Player(string sheetName, int tX, int tY);
	~Player();
};

#endif