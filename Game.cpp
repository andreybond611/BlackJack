#include "Game.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

void Game::initialize_text(sf::Text& text_to_initialize)
{
	text_to_initialize.setFont(font);
	text_to_initialize.setFillColor(sf::Color::Cyan);
	text_to_initialize.setCharacterSize(text_size);
}

Game::Game() :
	_window(sf::VideoMode(window_width, window_height), "Blackjack"),
	player(*this),
	dealer(*this)
{
	font.loadFromFile("arial.ttf");
	initialize_text(player_count_text);
	initialize_text(dealer_count_text);
	initialize_text(result_text);
	initialize_text(info_text);

	start();
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

void Game::dealer_wins()
{
	result_text.setString("Dealer wins");
	std::cout << "dealer wins";
	show_result = true;
	auto callback_to_set = [&]() { start(); };
	set_timer(1000, callback_to_set);
}

void Game::player_wins()
{
	result_text.setString("Player wins");
	std::cout << "player wins";
	show_result = true;
	auto callback_to_set = [&]() { start(); };
	set_timer(1000, callback_to_set);
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
				stand();
			}
		}
	}
}

void Game::hit()
{
	Card new_card = deck.give_card();
	player.take_card(new_card);
	int player_card_count = player.get_card_count();

	if (player_card_count > 21)
	{
		bust();
	}
}

void Game::stand()
{
	input_enabled = false;
	dealer.start_play();
}

void Game::update(sf::Time deltaTime)
{
	if (waiting_time > 0)
	{
		waiting_time -= deltaTime.asMicroseconds();
		std::cout << waiting_time << std::endl;
	}
	if (waiting_time <= 0 && call_after_wait)
	{
		call_after_wait = false;
		callback();
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
		result += x_step;
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

void Game::draw_cards_in_line(sf::RenderTarget& render_target, sf::Vector2f player_starting_position, std::vector<Card>& cards_to_draw, sf::Text& text_before_cards)
{
	float step_sum = {};
	text_before_cards.setPosition(0.f, player_starting_position.y + card_height / 2);
	render_target.draw(text_before_cards);
	for (Card& card : cards_to_draw)
	{
		render_target.draw(card);
		card.set_position(player_starting_position.x + step_sum, player_starting_position.y);
		step_sum += x_step;
	}
}

void Game::display_cards(sf::RenderTarget& render_target)
{
	std::vector<Card>& player_cards = player.get_cards();
	sf::Vector2f starting_position = calculate_card_starting_position(player_cards.size());

	sf::Vector2f player_starting_position = starting_position;
	player_starting_position.y += y_offset;

	sf::Text player_cards_text;
	initialize_text(player_cards_text);
	player_cards_text.setString("Player's Cards:");

	draw_cards_in_line(render_target, player_starting_position, player_cards, player_cards_text);


	std::vector<Card>& dealer_cards = dealer.get_cards();
	starting_position = calculate_card_starting_position(dealer_cards.size());

	sf::Vector2f dealer_starting_position = starting_position;
	dealer_starting_position.y -= y_offset;

	sf::Text dealer_cards_text;
	initialize_text(dealer_cards_text);
	dealer_cards_text.setString("Dealer's Cards:");

	draw_cards_in_line(render_target, dealer_starting_position, dealer_cards, dealer_cards_text);

}

void Game::display_text(sf::RenderTarget& render_target)
{
	if (player.get_card_count() > 21)
	{
		player_count_text.setString("busted!!");
	}
	else
	{
		std::string score_label = "player card count: ";
		player_count_text.setString(score_label + std::to_string(player.get_card_count()));
	}
	player_count_text.setPosition(0.f, 0.f);
	render_target.draw(player_count_text);

	if (dealer_plays)
	{
		if (dealer.get_card_count() > 21)
		{
			dealer_count_text.setString("busted!!");
		}
		else
		{
			std::string score_label = "dealer card count: ";
			dealer_count_text.setString(score_label + std::to_string(dealer.get_card_count()));
		}
		dealer_count_text.setPosition(0.f, text_size + 1.f);
		render_target.draw(dealer_count_text);
	}

	if (show_result)
	{
		result_text.setPosition(0.f, text_size * 2.f + 2.f);
		render_target.draw(result_text);
	}

	info_text.setString(R"("h" - hit, "s" - stand)");
	info_text.setPosition(0.f, window_height - text_size);
	render_target.draw(info_text);

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

std::vector<Card> Game::get_two_cards(bool to_dealer = false)
{
	std::vector<Card> cards;

	Card new_card = deck.give_card();
	Card new_card2 = deck.give_card();
	if (to_dealer)
	{
		new_card2.hide();
	}

	cards.push_back(new_card);
	cards.push_back(new_card2);

	return cards;
}

void Game::start()
{
	deck.shuffle();

	std::vector<Card> dealer_cards = get_two_cards(true);
	dealer.reset(dealer_cards);

	std::vector<Card> player_cards = get_two_cards();
	player.reset(player_cards);

	input_enabled = true;
	dealer_plays = false;
	show_result = false;
}

void Game::bust()
{
	input_enabled = false;
	auto callback_to_set = [&]() { start(); };
	set_timer(1000, callback_to_set);
}
