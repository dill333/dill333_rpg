#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;

class Tile
{
	sf::Rect<int> rect;
	int tileTypeX;
	int tileTypeY;
	int prop;
	int teleX;
	int teleY;
	sf::Sprite sprite;
public:
	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;
	static const enum properties {TP_NONE, TP_BLOCKED, TP_TELEPORT};
	Tile();
	Tile(int tileX, int tileY, int ttx, int tty, int p);
	void create(int tileX, int tileY, int ttx, int tty, int p);
	int getTileTypeX();
	int getTileTypeY();
	sf::Rect<int> getRect();
	int getProp();
	int getTeleX();
	int getTeleY();
	~Tile();
	friend ostream &operator<<(ostream &stream, Tile t);
	friend istream &operator>>(istream &stream, Tile &t);
};