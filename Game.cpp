#include "Game.h"

#include <thread>
#include <chrono>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

void Game::initialize_text(sf::Text& text_to_initialize)
{
	text_to_initialize.setFont(font);
	text_to_initialize.setFillColor(sf::Color::Cyan);
	text_to_initialize.setCharacterSize(text_size);
}

Game::Game() : _window(sf::VideoMode(window_width, window_height), "Blackjack")
{
	font.loadFromFile("arial.ttf");
	initialize_text(player_count_text);

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

			if (event.key.code == sf::Keyboard::H && is_input_enabled())
			{
				hit();
			}

			if (event.key.code == sf::Keyboard::S && is_input_enabled())
			{
				//stand();
			}
		}

		
	}
}

void Game::hit()
{
	Card new_card = deck.give_card();
	player_cards.push_back(new_card);
	player_card_count = calculate_card_count(player_cards);

	if (player_card_count > 21)
	{
		bust();
	}
}

void Game::update(sf::Time deltaTime)
{
	if (waiting_time > 0)
	{
		waiting_time -= deltaTime.asMilliseconds();
		std::cout << waiting_time << std::endl;
	}
	if (waiting_time <= 0 && init_after_wait)
	{
		init();
	}
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

void Game::draw_cards_in_line(sf::RenderTarget& render_target, sf::Vector2f player_starting_position, std::vector<Card>& cards_to_draw)
{
	float step_sum = {};
	for (Card& card : cards_to_draw)
	{
		render_target.draw(card);
		card.set_position(player_starting_position.x + step_sum, player_starting_position.y);
		step_sum += step;
	}
}

void Game::display_cards(sf::RenderTarget& render_target)
{
	float step_sum = 0.f;
	sf::Vector2f starting_position = calculate_card_starting_position(player_cards.size());

	sf::Vector2f player_starting_position = starting_position;
	player_starting_position.y += 80.f; // magic number
	draw_cards_in_line(render_target, player_starting_position, player_cards);

	starting_position = calculate_card_starting_position(dealer_cards.size());
	sf::Vector2f dealer_starting_position = starting_position;
	dealer_starting_position.y -= 80.f;
	draw_cards_in_line(render_target, dealer_starting_position, dealer_cards);

}

void Game::display_text(sf::RenderTarget& render_target)
{
	if (player_card_count > 21)
	{
		player_count_text.setString("busted!!");
	}
	else
	{
		std::string score_label = "card count: ";
		player_count_text.setString(score_label + std::to_string(player_card_count));
	}
	player_count_text.setPosition(0.f, 0.f);
	render_target.draw(player_count_text);
}

inline bool Game::is_input_enabled()const
{
	return input_enabled;
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

	player_cards.clear();
	dealer_cards.clear();

	Card new_card = deck.give_card();
	Card new_card2 = deck.give_card();

	player_cards.push_back(new_card);
	player_cards.push_back(new_card2);

	player_card_count = calculate_card_count(player_cards);
	input_enabled = true;
	init_after_wait = false;
}

void Game::wait_one_second_and_init()
{
	waiting_time = 200;
	init_after_wait = true;
}

void Game::bust()
{
	input_enabled = false;
	wait_one_second_and_init();
}

int Game::calculate_card_count(std::vector<Card>& cards)
{
	int count = 0;
	for (Card& card : cards)
	{
		count += card.get_count();
	}
	return count;
}
