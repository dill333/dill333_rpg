#include "Monster.h"
#include <iostream>

Monster::Monster(string shName, int tiX, int tiY) : Entity(shName, tiX, tiY)
{

	srand(time(NULL));
	tick = 1;

	// Update the sprite
	updateSprite();

}

void Monster::move()
{

	if(canMove)
	{
		if(tick % 60 == 0)
		{
			int m = rand() % 5;	// All directions, and not moving at all

			switch(m)
			{
			case up:
				tileY--;
				dir = up;
				canMove = false;
				continueMoving();
				break;
			case down:
				tileY++;
				dir = down;
				canMove = false;
				continueMoving();
				break;
			case left:
				tileX--;
				dir = left;
				canMove = false;
				continueMoving();
				break;
			case right:
				tileX++;
				dir = right;
				canMove = false;
				continueMoving();
			}
		
			tick = 1;
		}
		else
			frame = 0;
	}
	else
		continueMoving();

	// Make sure their in the bounds
	if(rect.Left < 0)
		rect.Left = 0;
	if(rect.Left > 768)
		rect.Left = 768;
	if(rect.Top < 0)
		rect.Top = 0;
	if(rect.Top > 608)
		rect.Top = 608;

	if(tileX < 0)
		tileX = 0;
	if(tileX > 24)
		tileX = 24;
	if(tileY < 0)
		tileY = 0;
	if(tileY > 19)
		tileY = 19;

	// 32x32 snap
	if(((rect.Left % 32) == 0) && ((rect.Top % 32) == 0))
		canMove = true;
	else
		canMove = false;

	// Update the sprite
	updateSprite();

}


Monster::~Monster()
{
}
