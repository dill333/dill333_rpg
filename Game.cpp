#include "Game.h"
#include "Player.h"

Game::Game()
{

	// Our render window
	window.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG");
	window.SetFramerateLimit(FPS);

	// Check to see that the map is loaded
	loaded = m.isLoaded();

}

void Game::run()
{

	// The main loop, make sure that everything initialized OK
	if(loaded)
	{
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

			m.tick();
			m.draw(&window);

			// Display the window
			window.Display();
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