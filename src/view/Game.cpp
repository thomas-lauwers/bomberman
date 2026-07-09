#include "../../include/view/Game.h"

#include "../../include/logic/state/PlayState.h"
using namespace std;

Game::Game() : window(sf::VideoMode({720, 624}), "Bomberman"),
               state_manager(make_unique<StateManager>()) {
    window.setFramerateLimit(60);
}

void Game::run() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        state_manager->handleInput();
        state_manager->update();

        window.clear();
        state_manager->render(window);
        window.display();
    }
}

void Game::addGameState(unique_ptr<State> state) const {
    state_manager->pushState(std::move(state));
}

