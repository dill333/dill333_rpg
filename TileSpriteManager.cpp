#include "TileSpriteManager.h"

TileSpriteManager::TileSpriteManager()
{
}

vector<sf::Sprite*> TileSpriteManager::sprites;
vector<sf::Vector3<int>> TileSpriteManager::loaded;

sf::Sprite *TileSpriteManager::getTileSprite(sf::Vector3<int> sheetXY)
{
	// sheetXY.x = tileSheetNum
	// sheetXY.y = tileX
	// sheetXY.z = tileY

	// See if we already loaded this sprite
	for(int i = 0; i < loaded.size(); i++)
	{
		if(sheetXY.x == loaded[i].x && sheetXY.y == loaded[i].y && sheetXY.z == loaded[i].z)
			return sprites[i];
	}

	// Must load a new sprite
	stringstream s;
	s<<"tiles"<<sheetXY.x<<".png";
	sf::Texture *texture = TextureManager::getTexture(s.str());
	if(texture != NULL)
	{
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		sprite->setTextureRect(sf::Rect<int>(sheetXY.y * Tile::TILE_WIDTH, sheetXY.z * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
		loaded.push_back(sheetXY);
		sprites.push_back(sprite);
		return sprites[sprites.size() - 1];
	}
	else	// Could not load the file
	{
		return NULL;
	}

}

TileSpriteManager::~TileSpriteManager()
{

	// Delete all of the sprites we used
	for(int i = 0; i < sprites.size(); i++)
		delete sprites[i];

}
