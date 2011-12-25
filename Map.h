#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "Player.h"
#include "Item.h"

class Map
{
	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;
	sf::Texture tileSheet;
	bool loadTileSheet();
	bool loadMap();
	bool loadDefaultMap();
	enum tileTypes{tt_blank, tt_brick, tt_grass, tt_purple, tt_black, tt_notfound};
	enum direction{up, down, left, right};
	sf::Sprite tileTypes[6];
	bool loaded;
	Tile tiles[25][20];
	std::vector<Entity*> entities;
	sf::RenderTexture mapTexture;
	sf::Sprite mapSprite;
	std::vector<Item*> items;
public:
	Map();
	bool getLoaded();
	Tile getTile(int i, int j);
	sf::Sprite getTileTypeSprite(int i);
	void checkCollisions(int k);
	void addEntity(Entity *e);
	Entity* getEnt(int x, int y);
	void attack(int i);
	void doLogic();
	void draw(sf::RenderWindow& window);
	void addItem(Item *i);
	bool save();
	~Map();
};

