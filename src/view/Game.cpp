#include "../../include/view/Game.h"
#include "../../include/logic/state/PlayState.h"
#include "../../include/utils/Stopwatch.h"
#include "../../include/utils/ViewportUtility.h"
#include "../../include/logic/World.h"
using namespace std;

Game::Game() : window(sf::VideoMode({720, 624}), "Bomberman"),
               state_manager(make_unique<StateManager>()) {
    window.setFramerateLimit(60);
}

void Game::run() {
    ViewportUtility::setViewport(window, static_cast<float>(World::WIDTH) / static_cast<float>(World::HEIGHT));

    while (window.isOpen())
    {
        Stopwatch::getInstance().update();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    ViewportUtility::setViewport(window, static_cast<float>(World::WIDTH) / static_cast<float>(World::HEIGHT));
                    break;
                default:
                    break;
            }

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

