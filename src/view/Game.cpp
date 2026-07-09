#include "../../include/view/Game.h"

#include "../../include/logic/PlayState.h"
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

