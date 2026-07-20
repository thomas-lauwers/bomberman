#include "../../../include/view/core/Game.h"
#include "../../../include/logic/Input.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/state/PlayState.h"
#include "../../../include/utils/Stopwatch.h"
#include "../../../include/view/ViewportUtility.h"
#include "../../../include/view/factory/BattleStageFactory.h"
using namespace std;

Game::Game()
    : window(sf::VideoMode({720, 624}), "Bomberman"), state_manager(make_unique<StateManager>()),
      worldRenderer(textureManager, window) {
    window.setFramerateLimit(60);
    textureManager.loadAssets();
    auto factory = make_shared<BattleStageFactory>(textureManager, worldRenderer);
    addGameState(make_unique<PlayState>(factory));
}

void Game::run() {
    ViewportUtility::setViewport(window, static_cast<float>(World::WIDTH) / static_cast<float>(World::HEIGHT));

    while (window.isOpen()) {
        utils::Stopwatch::getInstance().update();
        const auto deltaTime = static_cast<float>(utils::Stopwatch::getInstance().getDeltaTime());

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ViewportUtility::setViewport(window,
                                             static_cast<float>(World::WIDTH) / static_cast<float>(World::HEIGHT));
                break;
            default:
                break;
            }
        }

        if (auto* currentState = state_manager->getCurrentState()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
                currentState->handleInput(Input::MoveLeft);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
                currentState->handleInput(Input::MoveRight);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
                currentState->handleInput(Input::MoveUp);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
                currentState->handleInput(Input::MoveDown);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
                currentState->handleInput(Input::PlaceBomb);
        }
        state_manager->update(deltaTime, worldRenderer);

        window.clear();
        state_manager->getCurrentState()->render(worldRenderer);
        window.display();
    }
}

void Game::addGameState(unique_ptr<State> state) const { state_manager->pushState(std::move(state)); }
