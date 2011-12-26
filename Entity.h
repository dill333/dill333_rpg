#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"

using namespace std;

class Entity
{
protected:
	static const int ENTITY_WIDTH = 32;
	static const int ENTITY_HEIGHT = 32;
	enum direction{up, down, left, right};
	sf::Texture *entitySheet;
	sf::Sprite entitySprites[3][4];
	sf::Sprite sprite;
	bool loadEntitySheet(string sName);
	bool loaded;
	sf::Rect<int> rect;
	int frame;
	int dir;
	bool canMove;
	int tileX;
	int tileY;
	void updateSprite();
	int curHealth;
	int maxHealth;
	bool attacking;
	int attackStrength;
	bool dead;
	int tick;
	int healthTick;
public:
	Entity(string sheetName, int tX, int tY);
	bool getLoaded();
	virtual void move();
	void continueMoving();
	sf::Sprite getSprite();
	void moveBack();
	int getTileX();
	int getTileY();
	void draw(sf::RenderWindow& texture);
	void drawHealthBar(sf::RenderWindow& texture);
	int getCurHealth();
	int getMaxHealth();
	void hurt(int dam);
	bool getAttacking();
	int getAttackStrength();
	void attack();
	int getDir();
	void die();
	bool getDead();
	~Entity();
};

