#pragma once

#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "Dealer.h"
#include "Deck.h"
#include "Player.h"

constexpr int window_width = 800;
constexpr int window_height = 600;
constexpr int text_size = 24;

constexpr int max_cards_in_hand = 11;

constexpr int ideal_score = 21;
constexpr int hidden_card_index = 1;

enum class play_result
{
	player_has_less,
    player_has_equal,
    player_has_more
};

class Game
{
public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    void initialize_text(sf::Text& text_to_initialize);
    Game();
    void run(int frame_per_seconds);

    Deck& get_deck() { return deck; }
    Player& get_player() { return player; }
    void set_dealer_plays(bool does_dealer_play) { dealer_plays = does_dealer_play; }

    template <typename Callable>
    void set_timer(int time, Callable call_after_time)
    {
        waiting_time = time * 1000;
        call_after_wait = true;
        callback = call_after_time;
    }

    void dealer_wins();
    void player_wins();

private:
    void process_events();
    void update(sf::Time deltaTime);
   
    void render();
    std::vector<Card> get_two_cards(bool to_dealer);

    void start();
    void bust();
    void hit();
    void stand();

    void display_cards(sf::RenderTarget& render_target);
    void display_text(sf::RenderTarget& render_window);

    bool is_input_enabled()const;

    float get_width_of_cards_size(int size);
    sf::Vector2f calculate_card_starting_position(int displaying_cards_size);
    void draw_cards_in_line(sf::RenderTarget& render_target,
        sf::Vector2f player_starting_position, std::vector<Card>& cards_to_draw, sf::Text& text_before_cards);

    sf::RenderWindow _window;

    Deck deck;
    Player player;
    Dealer dealer;

    float x_step = 70.f;
    float y_offset = 80.f;

    sf::Font font;
    sf::Text player_count_text;
    sf::Text dealer_count_text;
    sf::Text result_text;
    sf::Text info_text;

    bool input_enabled = false;
    bool dealer_plays = false;
    bool show_result = false;

    int waiting_time = 0;
    bool call_after_wait = false;

    std::function<void()> callback;


    // TODO: bets
    // TODO: divide draw and update
    // TODO: aces count as 11 or 1
};

