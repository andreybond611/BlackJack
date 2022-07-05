#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

Game::Game() : _window(sf::VideoMode(window_width, window_height), "Blackjack")
{
	displaying_cards.push_back(deck.cards[11]);
	displaying_cards.push_back(deck.cards[13]);
	displaying_cards.push_back(deck.cards[14]);
	displaying_cards.push_back(deck.cards[15]);
	displaying_cards.push_back(deck.cards[16]);
	displaying_cards.push_back(deck.cards[17]);
	displaying_cards.push_back(deck.cards[18]);
	displaying_cards.push_back(deck.cards[19]);
	displaying_cards.push_back(deck.cards[23]);
	displaying_cards.push_back(deck.cards[20]);
	displaying_cards.push_back(deck.cards[25]);
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

float Game::get_width_of_card_count(int cards_count)
{
	float result = 0.f;

	if (cards_count < 1)
		return result;

	result = card_width;

	if (cards_count == 1)
		return result;

	for (int i = 1; i < cards_count; ++i)
	{
		result += step;
	}

	return result;
}

sf::Vector2f Game::calculate_starting_position(int displaying_cards_count)
{
	float x, y;
	x = window_width / 2 - get_width_of_card_count(displaying_cards_count) / 2;
	y = window_height / 2 - card_height / 2;

	return { x, y };
}

void Game::display_cards(sf::RenderTarget& render_target)
{
	float step_sum = 0.f;
	sf::Vector2f starting_position = calculate_starting_position(displaying_cards.size());
	for (Card& card : displaying_cards)
	{
		card.draw(render_target);
		card.set_position(starting_position.x + step_sum, starting_position.y);
		step_sum += step;
	}
}

void Game::render()
{
	_window.clear();
	display_cards(_window);
	_window.display();
}
