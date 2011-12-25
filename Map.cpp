#include "Map.h"

// TODO: Make this load the maps from the RPGMapEditor

bool Map::loadTileSheet()
{

	// Load the tile sheet
	if(tileSheet.LoadFromFile("tilesheet.png"))
	{
		// Cut up the tile sprites
		for(int i = 0; i < 6; i++)
		{
			tileTypes[i].SetTexture(tileSheet);
			tileTypes[i].SetSubRect(sf::Rect<int>(i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
		}
		return true;
	}
	else
		return false;

}

bool Map::loadMap()
{

	// Open the file
	ifstream file;
	file.open("room1.map");

	// Set up all of the tiles
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 25; j++)
		{
			if(file.good())
				file>>tiles[j][i];
			else
			{
				// EOF too early
				file.close();
				return loadDefaultMap();
			}
		}
	}

	// Close the file
	file.close();

	return true;

}

bool Map::loadDefaultMap()
{

	// Set up all of the tiles
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 25; j++)
			tiles[j][i] = Tile(j * 32, i * 32, tt_grass, false);

	return save();

}

Map::Map()
{
	
	// Initialize
	loaded = loadTileSheet();
	loaded &= loadMap();
	loaded &= mapTexture.Create(800, 640);

	// Clear the map texture
	mapTexture.Clear();

	// Draw all of the tiles to the texture
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			int tt = tiles[i][j].getTileType();
			sf::Sprite temp = tileTypes[tt];
			temp.SetX(i * 32);
			temp.SetY(j * 32);
			mapTexture.Draw(temp);
		}
	}
	
	// Done drawing, make the texture visible
	mapTexture.Display();

	// Set up the map sprite
	mapSprite = sf::Sprite(mapTexture.GetTexture());

}

bool Map::getLoaded()
{

	return loaded;

}

Tile Map::getTile(int i, int j)
{

	return tiles[i][j];

}

sf::Sprite Map::getTileTypeSprite(int i)
{

	return tileTypes[i];

}

void Map::checkCollisions(int k)
{

	int tx = entities[k]->getTileX();
	int ty = entities[k]->getTileY();
			
	// If they hit a blocked tile
	if(tiles[tx][ty].getBlocked())
		entities[k]->moveBack();
			
	// If they hit another entity
	for(int i = 0; i < entities.size(); i++)
	{
		if(i != k)
		{
			int ttx = entities[i]->getTileX();
			int tty = entities[i]->getTileY();

			if((tx == ttx) && (ty == tty))
				entities[k]->moveBack();
		}	
	}
}

void Map::addEntity(Entity *e)
{

	entities.push_back(e);

}

Entity* Map::getEnt(int x, int y)
{

	for(int i = 0; i < entities.size(); i++)
	{
		int tx = entities[i]->getTileX();
		int ty = entities[i]->getTileY();

		// Check to see if the entity is in the location
		if((tx == x) && (ty == y))
			return entities[i];
	}

	return NULL;

}

void Map::attack(int i)
{

	Entity *e = entities[i];
	int dir = e->getDir();
	int tx = e->getTileX();
	int ty = e->getTileY();

	Entity *e2 = NULL;

	// Attack wherever the entity is facing
	switch(dir)
	{
	case up:
		e2 = getEnt(tx, ty - 1);
		if(e2 != NULL)
			e2->hurt(e->getAttackStrength());
		break;
	case down:
		e2 = getEnt(tx, ty + 1);
		if(e2 != NULL)
			e2->hurt(e->getAttackStrength());
		break;
	case left:
		e2 = getEnt(tx - 1, ty);
		if(e2 != NULL)
			e2->hurt(e->getAttackStrength());
		break;
	case right:
		e2 = getEnt(tx + 1, ty);
		if(e2 != NULL)
			e2->hurt(e->getAttackStrength());
		break;
	}

}

void Map::doLogic()
{

	for(int i = 0; i < entities.size(); i++)
	{
		// Let this entity move
		entities[i]->move();

		// Check collisions
		checkCollisions(i);

		// See if this entity is attacking
		if(entities[i]->getAttacking())
			attack(i);

		// If this entity is dead, remove it
		if(entities[i]->getDead())
		{
			delete entities[i];
			entities.erase(entities.begin() + i);
		}
	}

}

void Map::draw(sf::RenderWindow& window)
{

	// Draw the map
	window.Draw(mapSprite);

	// Draw the items
	for(int i = 0; i < items.size(); i++)
		items.at(i)->draw(window);

	// Draw the entities
	for(int i = 0; i < entities.size(); i++)
		entities.at(i)->draw(window);

	// Draw the entity health bars
	for(int i = 0; i < entities.size(); i++)
			entities[i]->drawHealthBar(window);

}

void Map::addItem(Item *i)
{

	items.push_back(i);

}

bool Map::save()
{

	ofstream file;
	file.open("room1.map");

	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 25; j++)
			file<<tiles[j][i];

	file.close();

	return true;

}

Map::~Map()
{

	// Delete the memory we allocated for the entities
	for(int i = 0; i < entities.size(); i++)
		delete entities[i];

	entities.clear();

}
