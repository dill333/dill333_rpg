#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"
#include "TextureManager.h"

using namespace std;

class Player
{
	sf::Sprite sprites[3][4];
	sf::Sprite sprite;
	sf::Rect<int> rect;		// Where the player actually is
	int tileX;				// Where the player is going
	int tileY;				// ^
	int dir;
	int frame;
	bool moving;
	void updateSprite();
public:
	static const enum direction{DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
	static const int MAX_FRAME = 3;
	Player();
	Player(string sheetName, int tX, int tY);
	void tick();
	void draw(sf::RenderWindow *window);
	int getTileX();
	int getTileY();
	void setTileXY(int tX, int tY);
	void moveBack();
	~Player();
};

