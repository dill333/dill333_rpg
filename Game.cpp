#include "Game.h"
#include "Player.h"

Game::Game()
{

	// Our render window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG");
	window.setFramerateLimit(FPS);

	// Check to see that the map is loaded
	loaded = m.isLoaded();

}

void Game::run()
{

	// The main loop, make sure that everything initialized OK
	if(loaded)
	{
		while(window.isOpen())
		{
			sf::Event event;
			while(window.pollEvent(event))
			{
				// Request for closing the window
				if(event.type == sf::Event::Closed)
					window.close();
			}

			// Clear the window
			window.clear();

			m.tick();
			m.draw(&window);

			// Display the window
			window.display();
		}
	}
	else
	{
		cout<<"Error in initialization!  Press enter to quit.\n";
		cin.get();
	}

}

Game::~Game()
{
}