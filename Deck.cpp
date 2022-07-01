#include "Deck.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

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

std::string Deck::suit_to_string(Suit suit)
{
	switch(suit) { case hearts:
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
		switch(value)
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
