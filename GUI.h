#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Map.h"

class GUI
{
	sf::Texture guiTexture;
	sf::Sprite guiSprite;
	bool loaded;
	Inventory *inv;
	Map map;
	Player *player;
public:
	GUI();
	void draw(sf::RenderWindow& texture);
	bool getLoaded();
	void drawHealthBar(sf::RenderWindow& texture);
	void mousePushed(sf::RenderWindow& window);
	~GUI();
};

