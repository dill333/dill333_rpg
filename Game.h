#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace std;

class Game
{
	sf::RenderWindow window;
	Map m;
	bool loaded;
public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 640;
	static const int FPS = 30;
	Game();
	void run();
	~Game();
};

#endif