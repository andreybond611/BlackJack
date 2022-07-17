#include "Dealer.h"
#include "Game.h"

Dealer::Dealer(Game& played_game) :
Player(played_game)
{
}

void Dealer::start_play()
{
	get_cards()[hidden_card_index].unhide();
	game.set_dealer_plays(true);

	play();
}

void Dealer::play()
{
	int card_count = get_card_count();

	if (card_count > 21)
	{
		game.player_wins();
		return;
	}

	int player_card_count = game.get_player().get_card_count();

	if (card_count > player_card_count)
	{
		game.dealer_wins();
		return;
	}

	if (card_count < 17)
	{
		auto lambda = [&]()
		{
			Card card = game.get_deck().give_card();
			take_card(card);
			play();
		};
		game.set_timer(800, lambda);
		return;
	}

	if (card_count >= 17)
	{
		game.player_wins();
	}
}
