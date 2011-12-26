#include "TextureManager.h"

TextureManager::TextureManager()
{
}

vector<sf::Texture*> TextureManager::textures;
vector<string> TextureManager::loaded;

sf::Texture *TextureManager::getTexture(string str)
{

	// See if we have already loaded this texture
	for(int i = 0; i < loaded.size(); i++)
	{
		if(!str.compare(loaded.at(i)))
			return textures[i];
	}

	// Time to load the new texture
	sf::Texture *texture = new sf::Texture();
	if(texture->LoadFromFile(str))
	{
		loaded.push_back(str);
		textures.push_back(texture);
		return textures[textures.size() - 1];
	}
	else	// Could not load the file
	{
		delete texture;
		return NULL;
	}

}

TextureManager::~TextureManager()
{

	// Delete all of the textures we used
	for(int i = 0; i < textures.size(); i++)
		delete textures[i];

}
