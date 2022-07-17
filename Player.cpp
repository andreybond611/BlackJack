#include "Player.h"

Player::Player(Game& played_game)
	:game{played_game}
{
}

void Player::take_card(const Card& card)
{
	cards.push_back(card);
	calculate_card_count();
}

void Player::reset(std::vector<Card> starting_cards)
{
	cards.clear();
	cards.insert(cards.begin(), starting_cards.begin(), starting_cards.end());
	calculate_card_count();
}

void Player::calculate_card_count()
{
	int count = 0;
	for (Card& card : cards)
	{
		count += card.get_count();
	}
	card_count = count;
}
