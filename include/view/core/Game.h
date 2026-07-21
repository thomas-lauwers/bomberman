/**
 * @file Game.h
 * @brief Defines the Game class responsible for the main game loop and initialization.
 */

#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include "../../logic/state/StateManager.h"
#include "TextureManager.h"
#include "WorldRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>
using namespace std;

/**
 * @class Game
 * @brief Manages the main game loop, window creation, state management, and asset loading.
 */
class Game {
public:
    /**
     * @brief Constructs the Game object and initializes the main window.
     */
    Game();

    /**
     * @brief Runs the main game loop.
     */
    void run();

    /**
     * @brief Adds a new game state to the state manager.
     * @param state Unique pointer to the State to add.
     */
    void addGameState(unique_ptr<State> state) const;

private:
    sf::RenderWindow window;                ///< The main SFML rendering window
    unique_ptr<StateManager> state_manager; ///< The state manager managing game states
    TextureManager textureManager;          ///< Manager for loading and accessing textures
    WorldRenderer worldRenderer;            ///< The renderer responsible for drawing the game world
};

#endif // BOMBERMAN_GAME_H
