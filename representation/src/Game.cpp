#include "representation/Game.h"
#include "representation/StateManager.h"
#include "representation/ConcreteFactory.h"
#include "logic/Stopwatch.h"
#include <optional>

namespace rep {

Game::Game() : window(sf::VideoMode({800, 600}), "Bomberman") {
    factory = std::make_shared<ConcreteFactory>();
    world = std::make_shared<logic::World>(factory);
    stateManager = std::make_unique<StateManager>();
    world->initArena();
}

Game::~Game() = default;

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update(0.0f); // Logic uses its own Stopwatch singleton
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
        
        if (stateManager->getState() == GameState::Gameplay) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    world->playerPlaceBomb();
                }
            }
        }
    }

    if (stateManager->getState() == GameState::Gameplay) {
        float dx = 0, dy = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) dx -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) dx += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) dy += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) dy -= 1;
        
        if (dx != 0 || dy != 0) {
            world->movePlayer(dx, dy);
        }
    }
}

void Game::update(float) {
    if (stateManager->getState() == GameState::Gameplay) {
        world->update();
        factory->cleanup();
    }
}

void Game::render() {
    window.clear();
    if (stateManager->getState() == GameState::Gameplay) {
        for (auto& view : factory->getViews()) {
            window.draw(*view);
        }
    }
    window.display();
}

} // namespace rep
