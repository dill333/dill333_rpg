#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(int tileX, int tileY, int ttx, int tty, int p)
{

	// Set up the tile
	rect = sf::Rect<int>(tileX * TILE_WIDTH, tileY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
	tileTypeX = ttx;
	tileTypeY = tty;
	prop = p;
	teleX = 0;
	teleY = 0;

}

void Tile::create(int tileX, int tileY, int ttx, int tty, int p)
{

	// Set up the tile
	rect = sf::Rect<int>(tileX * TILE_WIDTH, tileY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
	tileTypeX = ttx;
	tileTypeY = tty;
	prop = p;
	teleX = 0;
	teleY = 0;

}

int Tile::getTileTypeX()
{

	return tileTypeX;

}

int Tile::getTileTypeY()
{

	return tileTypeY;

}

sf::Rect<int> Tile::getRect()
{

	return rect;

}

int Tile::getProp()
{

	return prop;

}

int Tile::getTeleX()
{

	return teleX;

}

int Tile::getTeleY()
{

	return teleY;

}

Tile::~Tile()
{
}

ostream &operator<<(ostream &stream, Tile t)
{

	stream<<t.rect.Left<<" "<<t.rect.Top<<" "<<t.tileTypeX<<" "<<t.tileTypeY<<" "<<t.prop;
	if(t.prop == Tile::TP_TELEPORT)
		stream<<" "<<t.teleX<<" "<<t.teleY;

	stream<<"\n";

	return stream;

}

istream &operator>>(istream &stream, Tile &t)
{

	stream>>t.rect.Left>>t.rect.Top>>t.tileTypeX>>t.tileTypeY>>t.prop;
	if(t.prop == Tile::TP_TELEPORT)
		stream>>t.teleX>>t.teleY;

	return stream;

}