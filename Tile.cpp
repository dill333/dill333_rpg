#include "Tile.h"

Tile::Tile()
{

	rect = sf::Rect<int>(0, 0, TILE_WIDTH, TILE_HEIGHT);
	tileType = 0;
	blocked = false;

}

Tile::Tile(int x, int y, int tt, bool b)
{

	rect = sf::Rect<int>(x, y, TILE_WIDTH, TILE_HEIGHT);
	tileType = tt;
	blocked = b;

}

int Tile::getTileType()
{

	return tileType;

}

bool Tile::getBlocked()
{

	return blocked;

}


Tile::~Tile()
{
}

ostream &operator<<(ostream &stream, Tile t)
{

	stream<<t.rect.Left<<" "<<t.rect.Top<<" "<<t.tileType<<" "<<t.blocked<<"\n";

	return stream;

}

istream &operator>>(istream &stream, Tile &t)
{

	stream>>t.rect.Left>>t.rect.Top>>t.tileType>>t.blocked;

	return stream;

}