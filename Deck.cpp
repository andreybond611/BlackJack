#include "Deck.h"
#include <iostream>
#include <random>
#include <SFML/Graphics/Texture.hpp>

std::array<sf::Texture, normal_deck_card_number> Deck::textures = {};

Deck::Deck()
{
	int card_count = 0;
	for (int suit_count = 0; suit_count < suits; ++suit_count)
	{
		for (int card_value = 1; card_value <= values; ++card_value)
		{

			Suit suit = static_cast<Suit>(suit_count);
			textures[card_count].loadFromFile(make_stringpath_to_card_png(suit, card_value));
			std::string card_name = value_to_string(card_value) + " of " + suit_to_string(suit);
			Card card = Card(textures[card_count], card_name, card_value, suit);
			cards.push_back(card);
			++card_count;
		}
	}
}

void Deck::shuffle()
{
	for (int i = normal_deck_card_number - 1; i > 0; i--)
	{
		int index = generate_random_number(0, cards.size() - 1);
		std::swap(cards[index], cards[i]);
	}
}

Card Deck::give_card()
{
	Card card = cards.back();
	cards.pop_back();
	discarded.push_back(card);
	return card;
}

std::string Deck::suit_to_string(Suit suit)
{
	switch (suit) {
	case hearts:
		return "hearts";
	case spades:
		return "spades";
	case diamonds:
		return "diamonds";
	case clubs:
		return "clubs";
	default:
		std::cout << "\nerror: invalid suit";
		return "invalid";
	}

}

std::string Deck::value_to_string(int value)
{
	if (value == 1 || value > 10)
	{
		switch (value)
		{
		case 1:
			return "ace";
		case 11:
			return "jack";
		case 12:
			return "queen";
		case 13:
			return "king";
		default:
			std::cout << "/nerror value";
			return "";
		}
	}
	return std::to_string(value);
}

std::string Deck::make_stringpath_to_card_png(Suit suit, int value)
{
	std::string result;
	std::string value_str = value_to_string(value);
	std::string suit_str = suit_to_string(suit);
	result = "card_pngs/" + value_str + "_" + suit_str + ".png";
	return result;
}

int Deck::generate_random_number(int min, int max)
{
	std::random_device random_device;
	std::seed_seq seed_sequence{ random_device(), random_device(), random_device(), random_device(), random_device(), random_device(), random_device(), random_device() };
	std::mt19937 mt{ seed_sequence };
	std::uniform_int_distribution<> random_num{ min, max };

	return random_num(mt);
}

