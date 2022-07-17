#pragma once
#include "Player.h"
class Game;

class Dealer : public Player
{
public:
	Dealer(Game& played_game);
	void start_play();
	void play();
};

