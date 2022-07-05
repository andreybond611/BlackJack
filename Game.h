#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Deck.h"

constexpr int window_width = 800;
constexpr int window_height = 600;
constexpr int text_size = 24;

constexpr int max_cards_in_hand = 11;

constexpr int ideal_score = 21;


class Game
{
public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game();
    void run(int frame_per_seconds);

private:
    void process_events();
    void update(sf::Time deltaTime);
   
    void render();

    void init();
    void calculate_card_count();

    void display_cards(sf::RenderTarget& render_target);
    void display_text(sf::RenderTarget& render_window);

    float get_width_of_cards_size(int size);
    sf::Vector2f calculate_card_starting_position(int displaying_cards_size);

    sf::RenderWindow _window;

    Deck deck;
    std::vector<Card> displaying_cards;
    float step = 70.f;

    sf::Font font;
    sf::Text count_text;
    sf::Vector2f text_position;

    int card_count = 0;

};
