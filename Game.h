#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

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
    void initialize_text(sf::Text& text_to_initialize);
    Game();
    void run(int frame_per_seconds);

private:
    void process_events();
    void update(sf::Time deltaTime);
   
    void render();

    void init();
    void bust();
    void hit();

    void display_cards(sf::RenderTarget& render_target);
    void display_text(sf::RenderTarget& render_window);

    bool is_input_enabled()const;
    void wait_one_second_and_init();
    int calculate_card_count(std::vector<Card>& cards);


    float get_width_of_cards_size(int size);
    sf::Vector2f calculate_card_starting_position(int displaying_cards_size);
    void draw_cards_in_line(sf::RenderTarget& render_target,
        sf::Vector2f player_starting_position, std::vector<Card>& cards_to_draw);

    sf::RenderWindow _window;

    Deck deck;
    std::vector<Card> player_cards;
    std::vector<Card> dealer_cards;
    float step = 70.f;

    sf::Font font;
    sf::Text player_count_text;
    sf::Text dealer_count_text;

    int player_card_count = 0;
    int dealer_card_count = 0;

    bool input_enabled = false;
    int waiting_time = 0;
    bool init_after_wait = false;
};

