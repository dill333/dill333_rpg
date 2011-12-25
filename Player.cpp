#include "Player.h"
#include <iostream>

Player::Player() : Entity("playersheet.png", 0, 0)
{

	// Update the sprite
	updateSprite();

	canAttack = true;

}

Player::Player(string shName, int tiX, int tiY) : Entity(shName, tiX, tiY)
{

	// Update the sprite
	updateSprite();

	canAttack = true;

}

void Player::move()
{

	// Move the player
	if(canMove)
	{
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left) || sf::Keyboard::IsKeyPressed(sf::Keyboard::A))
		{
			tileX--;
			dir = left;
			canMove = false;
			continueMoving();
		}
		else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right) || sf::Keyboard::IsKeyPressed(sf::Keyboard::D))
		{
			tileX++;
			dir = right;
			canMove = false;
			continueMoving();
		}
		else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up) || sf::Keyboard::IsKeyPressed(sf::Keyboard::W))
		{
			tileY--;
			dir = up;
			canMove = false;
			continueMoving();
		}
		else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down) || sf::Keyboard::IsKeyPressed(sf::Keyboard::S))
		{
			tileY++;
			dir = down;
			canMove = false;
			continueMoving();
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

	// Used for debugging
	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::X))
		hurt(1);

	// See if the player wants to attack
	if((sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) && canAttack)
	{
		attacking = true;
		canAttack = false;
		tick = 0;
	}
	else
		attacking = false;

	// Limit the attack speed
	if(tick > 10)
		canAttack = true;

	// Don't let tick get too big
	if(tick > 300)
		tick = 11;

}


Player::~Player()
{
}
