#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

Game::Game() : _window(sf::VideoMode(window_width, window_height), "Blackjack")
{
	font.loadFromFile("arial.ttf");
	count_text.setFont(font);
	count_text.setFillColor(sf::Color::Cyan);
	count_text.setCharacterSize(text_size);

	init();
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

			if (event.key.code == sf::Keyboard::H)
			{
				//hit();
			}
		}

		
	}
}

void Game::update(sf::Time deltaTime)
{
	
}

float Game::get_width_of_cards_size(int size)
{
	float result = 0.f;

	if (size < 1)
		return result;

	result = card_width;

	if (size == 1)
		return result;

	for (int i = 1; i < size; ++i)
	{
		result += step;
	}

	return result;
}

sf::Vector2f Game::calculate_card_starting_position(int displaying_cards_size)
{
	float x, y;
	x = window_width / 2 - get_width_of_cards_size(displaying_cards_size) / 2;
	y = window_height / 2 - card_height / 2;

	return { x, y };
}

void Game::display_cards(sf::RenderTarget& render_target)
{
	float step_sum = 0.f;
	sf::Vector2f starting_position = calculate_card_starting_position(displaying_cards.size());
	for (Card& card : displaying_cards)
	{
		render_target.draw(card);
		card.set_position(starting_position.x + step_sum, starting_position.y);
		step_sum += step;
	}
}

void Game::display_text(sf::RenderTarget& render_target)
{
	std::string score_label = "card count: ";
	count_text.setString(score_label + std::to_string(card_count));
	count_text.setPosition(0.f,0.f);
	render_target.draw(count_text);
}

void Game::render()
{
	_window.clear();
	display_text(_window);
	display_cards(_window);
	_window.display();
}

void Game::init()
{
	deck.shuffle();

	Card new_card = deck.give_card();
	Card new_card2 = deck.give_card();

	displaying_cards.push_back(new_card);
	displaying_cards.push_back(new_card2);

	calculate_card_count();
}

void Game::calculate_card_count()
{
	int count = 0;
	for (Card& card : displaying_cards)
	{
		count += card.get_count();
	}
	card_count = count;
}
