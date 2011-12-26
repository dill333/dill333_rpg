#include "GUI.h"

GUI::GUI()
{

	if(!guiTexture.LoadFromFile("gui.png"))
		loaded = false;
	else
		loaded = true;

	guiSprite = sf::Sprite(guiTexture);
	inv = NULL;

	loaded &= map.getLoaded();

	player = new Player("playersheet.png", 10, 10);

	map.addEntity(player);
	map.addEntity(new Monster("monstersheet.png", 5, 5));

	inv = new Inventory;

}

void GUI::draw(sf::RenderWindow& texture)
{

	// Draw the GUI stuff
	texture.Draw(guiSprite);

	// Draw the player's health bar
	if(player != NULL)
		drawHealthBar(texture);

	// Draw the inventory
	if(inv != NULL)
		inv->draw(texture);

	if(sf::Mouse::IsButtonPressed(sf::Mouse::Left))
		mousePushed(texture);

	// Do map logic and then draw the map
	map.doLogic();
	map.draw(texture);

}



bool GUI::getLoaded()
{

	return loaded;

}

void GUI::drawHealthBar(sf::RenderWindow& texture)
{

	// Draw the health bar for the player
	if(player != NULL)
	{
		float curHP = (float)player->getCurHealth();
		float maxHP = (float)player->getMaxHealth();

		texture.Draw(sf::Shape::Rectangle(sf::FloatRect(59, 668, (curHP / maxHP) * 100, 20), sf::Color::Red));
	}

}

void GUI::mousePushed(sf::RenderWindow& window)
{

	sf::Rect<int> *r = inv->getSlot(sf::Mouse::GetPosition(window));

}

GUI::~GUI()
{

	delete inv;

}
