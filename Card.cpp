#include "Card.h"
#include <SFML/Graphics/Texture.hpp>
#include <utility>
#include <SFML/Graphics/RenderTarget.hpp>

Card::Card(const sf::Texture& texture_to_set, std::string name_to_set,
           int value_to_set, Suit suit_to_set) :
	name(std::move(name_to_set)),
	value(value_to_set),
	count(get_count_from_value(value)), suit(suit_to_set)
{
	image.setTexture(texture_to_set);
}

Card::Card(const Card& copy) :
	image(copy.image),
	hidden_texture(copy.hidden_texture),
	name(copy.name),
	value(copy.value),
	count(copy.count),
	suit(copy.suit)
{
}

Card& Card::operator=(const Card& assign)
{
	if (this == &assign)
		return *this;

	image = assign.image;
	hidden_texture = assign.hidden_texture;
	name = assign.name;
	value = assign.value;
	count = assign.count;
	suit = assign.suit;
	return *this;
}

void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(image);
}

void Card::set_position(float x, float y)
{
	image.setPosition(x, y);
}

void Card::hide()
{
	hidden_texture = image.getTexture();
	sf::Texture null_texture;
	image.setTexture(null_texture);
	image.setColor(sf::Color::Green);
}

void Card::unhide()
{
	image.setColor(sf::Color::White);
	image.setTexture(*hidden_texture);
}

int Card::get_count_from_value(int value)
{
	if (value > 9)
		return 10;
	return value;
}
