#include "SpriteManager.h"

SpriteManager::SpriteManager()
{

	loaded = true;
	for(int i = 0; i < NUM_ENTS; i++)
		entTextures.push_back(sf::Texture());

	loaded &= entTextures.at(player).LoadFromFile("playersheet.png");
	loaded &= entTextures.at(monster).LoadFromFile("monstersheet.png");



}

bool SpriteManager::getLoaded()
{

	return loaded;

}

SpriteManager::~SpriteManager()
{
}
