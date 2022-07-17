#pragma once
#include <vector>

#include "Card.h"

class Game;

class Player
{
public:
	Player(Game& played_game);

	void take_card(const Card& card);
	void reset(std::vector<Card> starting_cards);
	int get_card_count()const { return card_count; }
	std::vector<Card>& get_cards() { return cards; }
protected:
	void calculate_card_count();
	Game& game;
private:
	std::vector<Card> cards;
	int card_count = 0;
};

