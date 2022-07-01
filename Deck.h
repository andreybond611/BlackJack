#pragma once
#include <array>
#include <vector>
#include "Card.h"
#include <SFML/Graphics/Texture.hpp>

constexpr int normal_deck_card_number = 52;
constexpr int suits = 4;
constexpr int values = 13;

class Deck
{
public:
	Deck();
	std::vector<Card> cards;
private:
	std::string suit_to_string(Suit suit);
	std::string value_to_string(int value);
	std::string make_stringpath_to_card_png(Suit suit, int value);

	std::array<sf::Texture, normal_deck_card_number> textures;
};

