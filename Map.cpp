#include "Map.h"

Map::Map()
{

	// If nothing goes wrong, this will still be true at the end
	loaded = true;
	loadedTileSheet = true;

	// Load the tile types
	sf::Texture *tileSheetTexture = TextureManager::getTexture("tilesheet.png");
	if(tileSheetTexture != NULL)
	{
		// Load the tile types
		for(int i = 0; i < NUM_TTX; i++)
		{
			for(int j = 0; j < NUM_TTY; j++)
			{
				tileTypes[i][j].setTexture(*tileSheetTexture);
				tileTypes[i][j].setTextureRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
			}
		}
	}
	else
		loadedTileSheet = false;

	// Set up the map texture
	mapTexture.create(MAP_WIDTH, MAP_HEIGHT);
	load("room1.map");

	p = new Player("playersheet.png", 5, 5);

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
			if(file.good())
				file>>tiles[j][i];
			else
			{
				// EOF too early
				file.close();
				loaded = false;
			}
		}
	}

	// Close the file
	file.close();

	updateSprite();

}

void Map::updateSprite()
{

	// Clear the map
	mapTexture.clear();

	// Make sure we have a map
	if(loaded)
	{
		// Set up the map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				// Get tile info
				int ttx = tiles[i][j].getTileTypeX();
				int tty = tiles[i][j].getTileTypeY();
				sf::Rect<int> rect = tiles[i][j].getRect();
				sf::Sprite temp;
				if((ttx < 0) || (ttx > NUM_TTX) || (tty < 0) || (tty > NUM_TTY))
				{
					loaded = false;
					temp = tileTypes[2][0];
				}
				else
					temp = tileTypes[ttx][tty];

				// Make sure whoever edited this file knew what they were doing
				if(((i * Tile::TILE_WIDTH) != rect.left) || ((j * Tile::TILE_HEIGHT) != rect.top))
					loaded = false;

				// Move the sprite to where we need to draw it
				temp.setPosition(rect.left, rect.top);
				mapTexture.draw(temp);
			}
		}
		mapTexture.display();
		mapSprite.setTexture(mapTexture.getTexture());
	}

	if(!loaded)
	{
		// Something went wrong, lets make the default map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				tiles[i][j].create(i, j, 2, 0, Tile::TP_NONE);
				sf::Sprite temp = tileTypes[2][0];
				temp.setPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
				mapTexture.draw(temp);
			}
		}
		// Save over the corrupt map with the default one
		save();
	}

	mapTexture.display();
	mapSprite.setTexture(mapTexture.getTexture());

}

void Map::save()
{

	// The file we will use
	ofstream file;
	file.open(mapName);

	// Set up all of the tiles
	for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
		for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
				file<<tiles[j][i];

	// Close the file
	file.close();

	loaded = true;

}

bool Map::isLoaded()
{

	return(loaded && loadedTileSheet);

}

void Map::checkCollisions()
{

	// Make sure the player isn't trying to go offscreen
	if((p->getTileY() < 0) || (p->getTileY() >= MAP_HEIGHT / Tile::TILE_HEIGHT) || (p->getTileX() < 0) || (p->getTileX() >= MAP_WIDTH / Tile::TILE_WIDTH))
		p->moveBack();

	// Make sure the player isn't trying to go through a blocked tile
	switch(tiles[p->getTileX()][p->getTileY()].getProp())
	{
	case Tile::TP_BLOCKED:
		p->moveBack();
		break;
	case Tile::TP_TELEPORT:
		int mn = tiles[p->getTileX()][p->getTileY()].getTeleMapNum();
		stringstream s;
		s<<"room"<<mn<<".map";
		if(s.str().compare(mapName))
			load(s.str());
		p->setTileXY(tiles[p->getTileX()][p->getTileY()].getTeleX(), tiles[p->getTileX()][p->getTileY()].getTeleY());
		break;
	}

}

void Map::tick()
{

	checkCollisions();
	p->tick();

}

void Map::draw(sf::RenderWindow *window)
{

	// Draw the map sprite
	window->draw(mapSprite);
	p->draw(window);

}

Map::~Map()
{

	delete p;

}