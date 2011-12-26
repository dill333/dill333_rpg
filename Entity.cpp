#include "Entity.h"
#include <iostream>

Entity::Entity(string sheetName, int tX, int tY)
{

	// Initialize
	loaded = loadEntitySheet(sheetName);
	tileX = tX;
	tileY = tY;
	rect = sf::Rect<int>(tileX * ENTITY_WIDTH, tileY * ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT);
	frame = 0;
	dir = up;
	sprite = entitySprites[frame][dir];
	canMove = true;
	curHealth = 100;
	maxHealth = 100;
	attacking = false;
	attackStrength = 10;
	dead = false;
	tick = 0;
	healthTick = 0;

}

bool Entity::loadEntitySheet(string sName)
{

	// Load the entity sheet
	entitySheet = TextureManager::getTexture(sName);
	if(entitySheet != NULL)
	{
		// Cut the entity sheet
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				entitySprites[j][i].SetTexture(*entitySheet);
				entitySprites[j][i].SetSubRect(sf::Rect<int>(j * ENTITY_WIDTH, i * ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
			}
		}
		return true;
	}
	else
		return false;
	
	/*if(entitySheet.LoadFromFile(sName))
	{
		// Cut the entity sheet
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				entitySprites[j][i].SetTexture(entitySheet);
				entitySprites[j][i].SetSubRect(sf::Rect<int>(j * ENTITY_WIDTH, i * ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
			}
		}
		return true;
	}
	else
		return false;*/

}

void Entity::updateSprite()
{

	// Change the sprite
	sprite = entitySprites[frame][dir];
	sprite.SetX(rect.Left);
	sprite.SetY(rect.Top);

}

bool Entity::getLoaded()
{

	return loaded;

}

void Entity::continueMoving()
{

	switch(dir)
	{
		case left:
			rect.Left -= 4;
			break;
		case right:
			rect.Left += 4;
			break;
		case up:
			rect.Top -= 4;
			break;
		case down:
			rect.Top += 4;
			break;
	}

	frame++;

	if(frame > 2)
		frame = 0;

	// Update the sprite
	updateSprite();

}

void Entity::moveBack()
{

	switch(dir)
	{
	case up:
		tileY++;
		break;
	case down:
		tileY--;
		break;
	case left:
		tileX++;
		break;
	case right:
		tileX--;
		break;
	}

	rect.Left = tileX * 32;
	rect.Top = tileY * 32;

	canMove = true;

	// Update the sprite
	updateSprite();

}

int Entity::getTileX()
{

	return tileX;

}

int Entity::getTileY()
{

	return tileY;

}

sf::Sprite Entity::getSprite()
{

	return sprite;

}

void Entity::move()
{

	// Needs to be overriden

}

void Entity::draw(sf::RenderWindow& texture)
{

	// Draw the entity's sprite
	texture.Draw(sprite);

	// Increment tick
	tick++;

}

void Entity::drawHealthBar(sf::RenderWindow& texture)
{

	// Draw a health bar
	if(healthTick >= 30)
	{
		texture.Draw(sf::Shape::Rectangle(sprite.GetPosition().x, sprite.GetPosition().y - 10, 32, 5, sf::Color::Black));	// The black background
		texture.Draw(sf::Shape::Rectangle(sprite.GetPosition().x, sprite.GetPosition().y - 10, ((float)curHealth / (float)maxHealth) * 32, 5, sf::Color::Red));		// The actual health bar
		healthTick++;	// Increment the health tick
	}
	
	// Been 5 seconds, stop drawing health bar
	if(healthTick >= 180)
		healthTick = 0;

}

int Entity::getCurHealth()
{

	return curHealth;

}

int Entity::getMaxHealth()
{

	return maxHealth;

}

void Entity::hurt(int dam)
{

	if(curHealth > 0)
		curHealth -= dam;
	
	if(curHealth <= 0)
		dead = true;

	// Start drawing the health bar
	healthTick = 30;

}

bool Entity::getAttacking()
{

	return attacking;

}

int Entity::getAttackStrength()
{

	return attackStrength;

}

void Entity::attack()
{

	attacking = true;

}

int Entity::getDir()
{

	return dir;

}

void Entity::die()
{

	dead = true;

}

bool Entity::getDead()
{

	return dead;

}

Entity::~Entity()
{
}
