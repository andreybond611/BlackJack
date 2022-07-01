#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>

enum Suit
{
	hearts,
	spades,
	diamonds,
	clubs
};

class sf::Texture;

class Card : public sf::Drawable
{
public:
	Card(const sf::Texture& texture_to_set, std::string name_to_set,
		int value_to_set, Suit suit_to_set);

	Card(const Card& copy);
	Card& operator=(const Card& assign);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	void set_position(float x, float y);

	std::string get_name()const { return name; }
	int get_value()const { return value; }
	Suit get_suit()const { return suit; }
private:
	sf::Sprite image;
	std::string name;
	int value;
	Suit suit;

};

