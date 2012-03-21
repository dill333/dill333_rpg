#include "Entity.h"
#include "Map.h"

Entity::Entity()
{
}

Entity::Entity(string sheetName, int tX, int tY)
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
			sprites[i][j].setTextureRect(sf::Rect<int>(i * rect.width, j * rect.height, rect.width, rect.height));
		}
	}

	// Set up the current sprite
	updateSprite();
	m = NULL;

}

void Entity::setMap(Map *ma)
{

	m = ma;

}

void Entity::tick()
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

		// Handle movement
		move();
	}

	updateSprite();

	if(m)
		m->checkCollisions(this);

}

void Entity::updateSprite()
{

	// Set up the current sprite
	sprites[frame][dir].setPosition(rect.left, rect.top);

}

void Entity::draw(sf::RenderWindow *window)
{

	// Draw it
	window->draw(sprites[frame][dir]);

}

int Entity::getTileX()
{

	return tileX;

}

int Entity::getTileY()
{

	return tileY;

}

void Entity::setTileXY(int tX, int tY)
{

	tileX = tX;
	tileY = tY;
	rect.left = tileX * rect.width;
	rect.top = tileY * rect.height;
	moving = false;

}

void Entity::moveBack()
{

	// Move the entity back
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

	rect.left = tileX * rect.width;
	rect.top = tileY * rect.height;
	moving = false;

}

Entity::~Entity()
{
}
