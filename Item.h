#pragma once

#include <SFML/Graphics.hpp>

class Item
{
	static const int ITEM_WIDTH = 32;
	static const int ITEM_HEIGHT = 32;

	sf::Rect<int> colRect;
	sf::Shape shape;
public:
	Item();
	Item(sf::Vector2<int> p);
	Item(int x, int y);
	Item(sf::Rect<int> r);
	void setPosition(sf::Vector2<int> pos);
	void setPosition(int x, int y);
	void draw(sf::RenderWindow& window);
	sf::Vector2<int> getPosition();
	~Item();
};

