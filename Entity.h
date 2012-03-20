#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"
#include "TextureManager.h"

using namespace std;

class Entity
{
protected:
	sf::Sprite sprites[3][4];
	sf::Rect<int> rect;		// Where the entity actually is
	int tileX;				// Where the entity is going
	int tileY;				// ^
	int dir;
	int frame;
	bool moving;
	void updateSprite();
	virtual void move() = 0;
public:
	static const enum direction{DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
	static const int MAX_FRAME = 3;
	Entity();
	Entity(string sheetName, int tX, int tY);
	virtual void tick();
	void draw(sf::RenderWindow *window);
	int getTileX();
	int getTileY();
	void setTileXY(int tX, int tY);
	void moveBack();
	~Entity();
};

#endif