#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"

class Inventory
{
	static const int SLOT_WIDTH = 32;
	static const int SLOT_HEIGHT = 32;
	sf::Rect<int> slots[3][4];
	std::vector<Item*> items;
public:
	Inventory();
	void draw(sf::RenderWindow& texture);
	sf::Rect<int>* getSlot(sf::Vector2<int> pos);
	void addItem(Item *i, int x, int y);
	void removeItem(int sx, int sy, int x, int y);
	~Inventory();
};

