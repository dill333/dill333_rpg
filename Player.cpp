#include "Player.h"

Player::Player()
{
}

Player::Player(string sheetName, int tX, int tY) : Entity(sheetName, tX, tY)
{
}

void Player::move()
{

	// Handle keypresses
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		tileY--;
		dir = DIR_UP;
		moving = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		tileY++;
		dir = DIR_DOWN;
		moving = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		tileX--;
		dir = DIR_LEFT;
		moving = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		tileX++;
		dir = DIR_RIGHT;
		moving = true;
	}

}

Player::~Player()
{
}
