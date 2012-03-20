#ifndef MONSTER_H
#define MONSTER_H

#include <stdlib.h>
#include <time.h>
#include "Entity.h"

class Monster : public Entity
{
	int go;
	void move();
public:
	Monster();
	Monster(string sheetName, int tX, int tY);
	~Monster();
};

#endif