#ifndef TILESPRITEMANAGER_H
#define TILESPRITEMANAGER_H

#include "TextureManager.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>

using namespace std;

class TileSpriteManager
{
	static const int NUM_TILE_SHEETS = 25;
	static const int NUM_TTX = 8;
	static const int NUM_TTY = 23;

	// The tile sprites that are loaded
	static vector<sf::Sprite*> sprites;

	// The info of each tile sprite loaded
	static vector<sf::Vector3<int>> loaded;

	// Constructor that is not used
	TileSpriteManager();
public:
	// Destructor which deletes the sprites previously loaded
	~TileSpriteManager();

	// Loads the sprite and returns a pointer to it
	// If it is already loaded, this function just returns it
	// If it cannot find the sprite, returns NULL
	static sf::Sprite *getTileSprite(sf::Vector3<int> sheetXY);
};

#endif