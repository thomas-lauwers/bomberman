#ifndef BOMBERMAN_REP_GAME_H
#define BOMBERMAN_REP_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "logic/World.h"

namespace rep {

class StateManager;
class ConcreteFactory;

/**
 * @brief Main game class handling the SFML window and main loop.
 */
class Game {
public:
    Game();
    ~Game();

    /**
     * @brief Run the game loop.
     */
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    std::shared_ptr<logic::World> world;
    std::shared_ptr<ConcreteFactory> factory;
    std::unique_ptr<StateManager> stateManager;
};

} // namespace rep

#endif // BOMBERMAN_REP_GAME_H
