#include "Map.h"

Map::Map()
{

	// If nothing goes wrong, this will still be true at the end
	loaded = true;
	loadedTileSheet = true;
	p = NULL;

	/*// Load the tile types
	sf::Texture *tileSheetTexture = TextureManager::getTexture("tiles0.png");
	if(tileSheetTexture != NULL)
	{
		// Load the tile types
		for(int i = 0; i < NUM_TTX; i++)
		{
			for(int j = 0; j < NUM_TTY; j++)
			{
				sf::Sprite* tt = new sf::Sprite();
				tt->setTexture(*tileSheetTexture);
				tt->setTextureRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
				tileTypes.push_back(tt);
				//tileTypes[i][j].setTexture(*tileSheetTexture);
				//tileTypes[i][j].setTextureRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
			}
		}
	}
	else
		loadedTileSheet = false;*/

	// Set up the map texture
	for(int i = 0; i < NUM_LAYERS; i++)
		mapTexture[i].create(MAP_WIDTH, MAP_HEIGHT);
	load("room1.map");

	loadPlayer();

}

void Map::load(string mN)
{

	// Set the map name
	mapName = mN;

	// Open the file we need
	ifstream file;
	file.open(mapName);

	// Set up all of the tiles
	for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
		{
			for(int k = 0; k < NUM_LAYERS; k++)
			{
				if(file.good())
					file>>tiles[k][j][i];
				else
				{
					// EOF too early
					file.close();
					loaded = false;
				}
			}
		}
	}

	// Close the file
	file.close();

	// Before we load the entities, we must get rid of the ones from the last map
	for(int i = 0; i < entities.size(); i++)
		delete entities[i];

	entities.clear();

	loadEntities();

	updateSprite();

}

void Map::loadPlayer()
{

	// Load the player
	if(loaded)
	{
		for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
		{
			for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
			{
				if(tiles[0][i][j].getProp() == Tile::TP_PSPAWN)
				{
					p = new Player("playersheet.png", i, j);
					p->setMap(this);
					return;
				}
			}
		}
	}

	// Couldn't find the player spawn, must set it
	p = new Player("playersheet.png", 0, 0);
	p->setMap(this);


}

void Map::loadEntities()
{

	// Load the entities
	if(loaded)
	{
		for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
		{
			for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
			{
				if(tiles[0][i][j].getProp() == Tile::TP_MSPAWN)
					entities.push_back(new Monster("monstersheet.png", i, j));
			}
		}
		for(int i = 0; i < entities.size(); i++)
			entities[i]->setMap(this);
	}

}

void Map::updateSprite()
{

	// Clear the map
	for(int i = 0; i < NUM_LAYERS; i++)
		mapTexture[i].clear(sf::Color(0, 0, 0, 0));

	// Make sure we have a map
	if(loaded)
	{
		// Set up the map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				for(int k = 0; k < NUM_LAYERS; k++)
				{
					// Get tile info
					int tsn = tiles[k][i][j].getTileSheetNum();
					int ttx = tiles[k][i][j].getTileTypeX();
					int tty = tiles[k][i][j].getTileTypeY();
					sf::Rect<int> rect = tiles[k][i][j].getRect();
					sf::Sprite temp;
					if((ttx < 0) || (ttx > NUM_TTX) || (tty < 0) || (tty > NUM_TTY))
					{
						loaded = false;
						if(k == 0)
							temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 1, 0));
						else
							temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 0, 0));
					}
					else
						temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(tsn, ttx, tty));

					// Make sure whoever edited this file knew what they were doing
					if(((i * Tile::TILE_WIDTH) != rect.left) || ((j * Tile::TILE_HEIGHT) != rect.top))
						loaded = false;

					// Move the sprite to where we need to draw it
					temp.setPosition(rect.left, rect.top);
					mapTexture[k].draw(temp);
				}
			}
		}
		for(int i = 0; i < NUM_LAYERS; i++)
		{
			mapTexture[i].display();
			mapSprite[i].setTexture(mapTexture[i].getTexture());
		}
	}

	if(!loaded)
	{
		// Something went wrong, lets make the default map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				for(int k = 0; k < NUM_LAYERS; k++)
				{
					sf::Sprite temp;
					if(k == 0)
					{
						tiles[k][i][j].create(0, i, j, 1, 0, Tile::TP_NONE);
						temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 1, 0));
					}
					else
					{
						tiles[k][i][j].create(0, i, j, 0, 0, Tile::TP_NONE);
						temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 0, 0));
					}	
					temp.setPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
					mapTexture[k].draw(temp);
				}
			}
		}
		tiles[0][0][0].create(0, 0, 0, 1, 0, Tile::TP_PSPAWN);
		// Save over the corrupt map with the default one
		save();
	}

	for(int i = 0; i < NUM_LAYERS; i++)
	{
		mapTexture[i].display();
		mapSprite[i].setTexture(mapTexture[i].getTexture());
	}

}

void Map::save()
{

	// The file we will use
	ofstream file;
	file.open(mapName);

	// Set up all of the tiles
	for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
		for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
			for(int k = 0; k < NUM_LAYERS; k++)
				file<<tiles[k][j][i];

	// Close the file
	file.close();

	loaded = true;

}

bool Map::isLoaded()
{

	return(loaded && loadedTileSheet);

}

void Map::checkCollisions(Entity *e)
{

	// Make sure the entity does not try to move off the map
	if((e->getTileY() < 0) || (e->getTileY() >= MAP_HEIGHT / Tile::TILE_HEIGHT) || (e->getTileX() < 0) || (e->getTileX() >= MAP_WIDTH / Tile::TILE_WIDTH))
		e->moveBack();

	if(e == p)
	{
		// Make sure the player does not try to move into the entities
		for(int i = 0; i < entities.size(); i++)
		{
			if((entities[i]->getTileX() == p->getTileX()) && (entities[i]->getTileY() == p->getTileY()))
				p->moveBack();
		}

		switch(tiles[0][p->getTileX()][p->getTileY()].getProp())
		{
		case Tile::TP_BLOCKED:
			p->moveBack();
			break;
		case Tile::TP_TELEPORT:
			int mn = tiles[0][p->getTileX()][p->getTileY()].getTeleMapNum();
			stringstream s;
			s<<"room"<<mn<<".map";
			if(s.str().compare(mapName))
				load(s.str());
			p->setTileXY(tiles[0][p->getTileX()][p->getTileY()].getTeleX(), tiles[0][p->getTileX()][p->getTileY()].getTeleY());
			break;
		}
	}
	else
	{
		for(int i = 0; i < entities.size(); i++)
		{
			if(e != entities[i])
			{
				// Make sure the entity does not try to move into the other entities
				if((e->getTileX() == entities[i]->getTileX()) && (e->getTileY() == entities[i]->getTileY()))
					e->moveBack();
			}
		}

		// Make sure the entity does not try to move into the player
		if((e->getTileX() == p->getTileX()) && (e->getTileY() == p->getTileY()))
			e->moveBack();

		switch(tiles[0][e->getTileX()][e->getTileY()].getProp())
		{
		case Tile::TP_BLOCKED:
			e->moveBack();
			break;
		}
	}

}

void Map::tick()
{

	if(p != NULL)
		p->tick();
	
	for(int i = 0; i < entities.size(); i++)
		entities[i]->tick();
	
}

void Map::draw(sf::RenderWindow *window)
{

	// Draw the map sprite
	window->draw(mapSprite[0]);
	p->draw(window);

	for(int i = 0; i < entities.size(); i++)
		entities[i]->draw(window);

	window->draw(mapSprite[1]);

}

Map::~Map()
{

	delete p;

	for(int i = 0; i < entities.size(); i++)
		delete entities[i];

	entities.clear();

}