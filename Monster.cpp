#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(string sheetName, int tX, int tY) : Entity(sheetName, tX, tY)
{

	go = 0;
	srand(time(NULL));

}

void Monster::move()
{

	// Set the movement for the monster
	go++;
	go %= 30;
	if(!go)
	{
		switch(rand() % 5)
		{
		case DIR_UP:
			tileY--;
			dir = DIR_UP;
			moving = true;
			break;
		case DIR_DOWN:
			tileY++;
			dir = DIR_DOWN;
			moving = true;
			break;
		case DIR_LEFT:
			tileX--;
			dir = DIR_LEFT;
			moving = true;
			break;
		case DIR_RIGHT:
			tileX++;
			dir = DIR_RIGHT;
			moving = true;
			break;
		}
	}

}

Monster::~Monster()
{
}
