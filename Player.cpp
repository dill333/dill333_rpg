#include "Player.h"

Player::Player()
{
}

Player::Player(string sheetName, int tX, int tY)
{

	// Initialize
	tileX = tX;
	tileY = tY;
	moving = false;
	dir = DIR_LEFT;
	frame = 0;
	rect.left = tileX * Tile::TILE_WIDTH;
	rect.top = tileY * Tile::TILE_HEIGHT;
	rect.width = Tile::TILE_WIDTH;
	rect.height = Tile::TILE_HEIGHT;

	// Set up the sprites and cut them out
	for(int i = 0; i < MAX_FRAME; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			sprites[i][j].setTexture(*TextureManager::getTexture(sheetName));
			sprites[i][j].setTextureRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
		}
	}

	// Set up the current sprite
	updateSprite();

}

void Player::updateSprite()
{

	// Set up the current sprite
	sprite = sprites[frame][dir];
	sprite.setPosition(rect.left, rect.top);

}

void Player::tick()
{

	// Change the frame and movement
	if(moving)
	{
		frame++;
		if(frame >= MAX_FRAME)
			frame = 0;
		
		// Move the player
		switch(dir)
		{
		case DIR_UP:
			rect.top -= Tile::TILE_HEIGHT / 8;
			break;
		case DIR_DOWN:
			rect.top += Tile::TILE_HEIGHT / 8;
			break;
		case DIR_LEFT:
			rect.left -= Tile::TILE_WIDTH / 8;
			break;
		case DIR_RIGHT:
			rect.left += Tile::TILE_WIDTH / 8;
			break;
		}

		// Check to see if we need to stop moving
		if((rect.left == tileX * Tile::TILE_WIDTH) && (rect.top == tileY * Tile::TILE_HEIGHT))
			moving = false;
	}
	else
	{
		// Reset everything
		frame = 0;
		rect.left = tileX * Tile::TILE_WIDTH;
		rect.top = tileY * Tile::TILE_HEIGHT;

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

	updateSprite();

}

void Player::draw(sf::RenderWindow *window)
{

	// Draw it
	window->draw(sprite);

}

int Player::getTileX()
{

	return tileX;

}

int Player::getTileY()
{

	return tileY;

}

void Player::setTileXY(int tX, int tY)
{

	tileX = tX;
	tileY = tY;
	rect.left = tileX * Tile::TILE_WIDTH;
	rect.top = tileY * Tile::TILE_HEIGHT;
	moving = false;

}

void Player::moveBack()
{

	// Move the player back
	switch(dir)
	{
	case DIR_UP:
		tileY++;
		break;
	case DIR_DOWN:
		tileY--;
		break;
	case DIR_LEFT:
		tileX++;
		break;
	case DIR_RIGHT:
		tileX--;
		break;
	}

	rect.left = tileX * Tile::TILE_WIDTH;
	rect.top = tileY * Tile::TILE_HEIGHT;
	moving = false;

}

Player::~Player()
{
}
