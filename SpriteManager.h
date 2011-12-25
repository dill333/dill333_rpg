#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

class SpriteManager
{
	static const int NUM_ENTS = 2;
	vector<sf::Texture> entTextures;
	vector<sf::Sprite> entSprites;
	enum entName{player, monster};
	bool loaded;
public:
	SpriteManager();
	bool getLoaded();
	~SpriteManager();
};

