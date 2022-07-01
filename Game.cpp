#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

Game::Game() : _window(sf::VideoMode(800, 600), "SFML - yay")
{
	
}

void Game::run(int minimum_frame_per_seconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / minimum_frame_per_seconds);
	while (_window.isOpen())
	{
		process_events();
		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) 
		{
			timeSinceLastUpdate -= TimePerFrame;
			update(TimePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
	}
}

void Game::process_events()
{
	sf::Event event{};
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
		}
		
	}
}

void Game::update(sf::Time deltaTime)
{
	
}

void Game::render()
{
	_window.clear();
	deck.cards[0].draw(_window);
	_window.display();
}