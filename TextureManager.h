#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

class TextureManager
{
	// The textures that are loaded
	static vector<sf::Texture*> textures;

	// The names of each texture loaded
	static vector<string> loaded;

	// Constructor that is not used
	TextureManager();
public:
	// Destructor which deletes the textures previously loaded
	~TextureManager();

	// Loads the texture and returns a pointer to it
	// If it is already loaded, this function just returns it
	// If it cannot find the file, returns NULL
	static sf::Texture *getTexture(string str);
};

#endif