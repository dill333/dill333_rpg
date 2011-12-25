#include "Inventory.h"

Inventory::Inventory()
{

	// Set up the slots
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			slots[j][i] = sf::Rect<int>(829 + (j * 35), 173 + (i * 35), SLOT_WIDTH, SLOT_HEIGHT);
		}
	}

}

void Inventory::draw(sf::RenderWindow& texture)
{

	// Draw the items
	for(int i = 0; i < items.size(); i++)
		items.at(i)->draw(texture);

}

sf::Rect<int>* Inventory::getSlot(sf::Vector2<int> pos)
{

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(slots[j][i].Contains(pos))
				return &slots[j][i];
		}
	}

	return NULL;

}

void Inventory::addItem(Item *i, int x, int y)
{

	i->setPosition(slots[x][y].Left, slots[x][y].Top);
	items.push_back(i);

}

void Inventory::removeItem(int sx, int sy, int x, int y)
{

	for(int i = 0; i < items.size(); i++)
	{
		if((items.at(i)->getPosition().x == sx) && (items.at(i)->getPosition().y == sy))
		{
			items.at(i)->setPosition(x, y);
			items.push_back(items.at(i));
		}
	}

}

Inventory::~Inventory()
{
}
