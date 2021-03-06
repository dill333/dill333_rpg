#ifndef MAP_H
#define MAP_H

#include <string>
#include <sstream>
#include <vector>
#include "Tile.h"
#include "TextureManager.h"
#include "TileSpriteManager.h"
#include "Player.h"
#include "Monster.h"
#include "iostream"

using namespace std;

class Map
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	static const int NUM_TTX = 8;
	static const int NUM_TTY = 23;
	static const int NUM_LAYERS = 2;
	sf::RenderTexture mapTexture[NUM_LAYERS];
	sf::Sprite mapSprite[NUM_LAYERS];
	Tile tiles[NUM_LAYERS][MAP_WIDTH / Tile::TILE_WIDTH][MAP_HEIGHT / Tile::TILE_HEIGHT];
	bool loaded;
	bool loadedTileSheet;
	Player *p;
	string mapName;
	vector<Entity*> entities;
	void updateSprite();
	void loadPlayer();
	void loadEntities();
public:
	Map();
	void load(string mN);
	void save();
	bool isLoaded();
	void checkCollisions(Entity *e);
	void tick();
	void draw(sf::RenderWindow *window);
	~Map();
};

#endif