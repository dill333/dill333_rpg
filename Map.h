#pragma once

#include "Tile.h"
#include "TextureManager.h"
#include "Player.h"

class Map
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	static const int NUM_TTX = 4;
	static const int NUM_TTY = 4;
	sf::Sprite tileTypes[NUM_TTX][NUM_TTY];
	sf::RenderTexture mapTexture;
	sf::Sprite mapSprite;
	Tile tiles[MAP_WIDTH / Tile::TILE_WIDTH][MAP_HEIGHT / Tile::TILE_HEIGHT];
	bool loaded;
	bool loadedTileSheet;
	Player *p;
	void checkCollisions();
public:
	Map();
	void save();
	bool isLoaded();
	void tick();
	void draw(sf::RenderWindow *window);
	~Map();
};