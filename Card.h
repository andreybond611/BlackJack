#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>

constexpr float card_height = 94.f;
constexpr float card_width = 64.f;

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
	int get_count()const { return count; }
	Suit get_suit()const { return suit; }
private:
	int get_count_from_value(int value);

	sf::Sprite image;
	std::string name;
	int value;
	int count;
	Suit suit;

};

