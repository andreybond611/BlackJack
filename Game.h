#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
    sf::RenderWindow _window;
};
