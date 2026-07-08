#include "../../include/view/Game.h"

Game::Game() : window(sf::VideoMode({800, 600}), "Bomberman") {}

void Game::run() {
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        window.display();
    }
}

