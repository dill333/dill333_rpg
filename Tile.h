#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;

class Tile
{
	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;
	sf::Rect<int> rect;
	int tileType;
	bool blocked;
public:
	Tile();
	Tile(int x, int y, int tt, bool b);
	int getTileType();
	bool getBlocked();
	~Tile();
	friend ostream &operator<<(ostream &stream, Tile t);
	friend istream &operator>>(istream &stream, Tile &t);
};

