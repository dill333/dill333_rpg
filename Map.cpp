#include "Map.h"

Map::Map()
{

	// If nothing goes wrong, this will still be true at the end
	loaded = true;

	// Open the file we need
	ifstream file;
	file.open("room1.map");

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

	// Load the tile types
	sf::Texture *tileSheetTexture = TextureManager::getTexture("tilesheet.png");
	if(tileSheetTexture != NULL)
	{
		// Load the tile types
		for(int i = 0; i < NUM_TTX; i++)
		{
			for(int j = 0; j < NUM_TTY; j++)
			{
				tileTypes[i][j].SetTexture(*tileSheetTexture);
				tileTypes[i][j].SetSubRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
			}
		}
	}
	else
		loadedTileSheet = false;

	// Set up the map texture
	mapTexture.Create(MAP_WIDTH, MAP_HEIGHT);
	mapTexture.Clear();

	if(loaded)
	{
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				// Get tile info
				int ttx = tiles[i][j].getTileTypeX();
				int tty = tiles[i][j].getTileTypeY();
				sf::Rect<int> rect = tiles[i][j].getRect();
				sf::Sprite temp = tileTypes[ttx][tty];

				// Make sure whoever edited this file knew what they were doing
				if(((i * Tile::TILE_WIDTH) != rect.Left) || ((j * Tile::TILE_HEIGHT) != rect.Top))
					loaded = false;

				// Move the sprite to where we need to draw it
				temp.SetPosition(rect.Left, rect.Top);
				mapTexture.Draw(temp);
			}
		}
		mapTexture.Display();
		mapSprite.SetTexture(mapTexture.GetTexture());
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
				temp.SetPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
				mapTexture.Draw(temp);
			}
		}
		// Save over the corrupt map with the default one
		save();
	}

	mapTexture.Display();
	mapSprite.SetTexture(mapTexture.GetTexture());

	p = new Player("playersheet.png", 5, 5);

}

void Map::save()
{

	// The file we will use
	ofstream file;
	file.open("room1.map");

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
		p->setTileX(tiles[p->getTileX()][p->getTileY()].getTeleX());
		p->setTileY(tiles[p->getTileX()][p->getTileY()].getTeleY());
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
	window->Draw(mapSprite);
	p->draw(window);

}

Map::~Map()
{

	delete p;

}