#include "pch.h"

#include "App.hpp"
#include "Game.hpp"

App::App()
{
	try
	{
		window = new sf::RenderWindow(sf::VideoMode(300, 361), "Tetris");
	}
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

int App::StartApp()
{
	sf::Event *event = new sf::Event;
	Game *game = new Game;	
	sf::Clock clock;
	
	while (window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == sf::Event::Closed) { window->close(); }
			game->Event(window, event);
		}

		if (game->isRunning()) { game->UpDate(clock.restart()); }		

		window->clear();
		
		game->Render(window);

		window->display();
	}

	delete event;
	delete game;

	return 0;
}

App::~App()
{
	delete window;
}
