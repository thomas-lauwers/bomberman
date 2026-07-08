#include "../../include/view/Game.h"
using namespace std;

Game::Game() : window(sf::VideoMode({800, 600}), "Bomberman"),
               state_manager(make_unique<StateManager>()){}

void Game::run() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // Pass input events to state manager here if needed
        }

        window.clear();

        // draw everything here...
        // window.draw(...);

        window.display();
    }
}

