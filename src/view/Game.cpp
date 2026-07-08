#include "../../include/view/Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Bomberman") {}

void Game::run() {
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        window.display();
    }
}
