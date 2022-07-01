#include "Card.h"
#include <SFML/Graphics/Texture.hpp>
#include <utility>
#include <SFML/Graphics/RenderTarget.hpp>

Card::Card(const sf::Texture& texture_to_set, std::string name_to_set,
           int value_to_set, Suit suit_to_set) :
	name(std::move(name_to_set)),
	value(value_to_set),
	suit(suit_to_set)
{
	image.setTexture(texture_to_set);
}

Card::Card(const Card& copy) :
	image(copy.image),
	name(copy.name),
	value(copy.value),
	suit(copy.suit)
{
}

Card& Card::operator=(const Card& assign)
{
	if (this == &assign)
		return *this;

	image = assign.image;
	name = assign.name;
	value = assign.value;
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