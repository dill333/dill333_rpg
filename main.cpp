#include <SFML/Graphics.hpp>
#include "GUI.h"

// TODO: Inventory stuff
// TODO: Items
// TODO: Equipment
// TODO: All GUI stuff
// TODO: Make a blood splat when entities die
// TODO: Make the game stop when the player dies, or at least stop drawing the health bar
// TODO: Better AI, specifically path finding (A*)

/* Structure:
main has GUI
GUI has Map and Inventory
Map has items, entities, tiles, and other map stuff
Inventory has the items it is using
GUI controls mouse events
Need to get sprites from a sprite manager, instead of loading a new sheet every time there is a new entity!
*/

static const int GAME_WIDTH = 800;
static const int GAME_HEIGHT = 640;
static const int WINDOW_WIDTH = 960;
static const int WINDOW_HEIGHT = 768;
static const int FPS = 30;

int main()
{

	// Our render window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG");

	// Limit the framerate
	window.SetFramerateLimit(FPS);

	// The GUI
	GUI gui;

	if(!gui.getLoaded())
		return 1;

	// The main loop
	while(window.IsOpened())
	{
		sf::Event event;
		while(window.PollEvent(event))
		{
			// Request for closing the window
			if(event.Type == sf::Event::Closed)
				window.Close();
		}

		// Clear the window
		window.Clear();

		// Draw the gui
		gui.draw(window);

		// Display the contents on the screen
		window.Display();
	}

	return 0;

}