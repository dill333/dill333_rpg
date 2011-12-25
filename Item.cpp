#include "Item.h"

Item::Item()
{



}

Item::Item(sf::Vector2<int> p)
{

	colRect.Left = p.x;
	colRect.Top = p.y;
	colRect.Width = ITEM_WIDTH;
	colRect.Height = ITEM_HEIGHT;
	shape = sf::Shape::Rectangle((sf::Rect<float>)colRect, sf::Color::Blue);

}

Item::Item(int x, int y)
{

	colRect.Left = x;
	colRect.Top = y;
	colRect.Width = ITEM_WIDTH;
	colRect.Height = ITEM_HEIGHT;
	shape = sf::Shape::Rectangle((sf::Rect<float>)colRect, sf::Color::Blue);

}

Item::Item(sf::Rect<int> r)
{

	colRect = r;

	shape = sf::Shape::Rectangle((sf::Rect<float>)colRect, sf::Color::Blue);

}

void Item::setPosition(sf::Vector2<int> pos)
{

	colRect.Left = pos.x;
	colRect.Top = pos.y;

	shape.SetX(colRect.Left);
	shape.SetY(colRect.Top);

}

void Item::setPosition(int x, int y)
{

	colRect.Left = x;
	colRect.Top = y;

	shape.SetX(colRect.Left);
	shape.SetY(colRect.Top);

}

void Item::draw(sf::RenderWindow& window)
{

	window.Draw(shape);

}

sf::Vector2<int> Item::getPosition()
{

	return sf::Vector2<int>(colRect.Left, colRect.Top);

}

Item::~Item()
{
}
