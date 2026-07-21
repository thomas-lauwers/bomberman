/**
 * @file PlayState.h
 * @brief Defines the PlayState class for the game simulation.
 */

#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H

#include "../IWorldView.h"
#include "../Input.h"
#include "../World.h"
#include "../Score.h"
#include "State.h"
#include <memory>

class IEntityFactory;

/**
 * @class PlayState
 * @brief Represents the active game simulation state.
 */
class PlayState : public State {
public:
    ~PlayState() override;
    
    /**
     * @brief Constructs a new PlayState instance.
     * @param factory Shared pointer to the entity factory.
     */
    explicit PlayState(std::shared_ptr<IEntityFactory> factory);

    /**
     * @brief Handles user input during gameplay.
     * @param input The input action.
     */
    void handleInput(Input input) override;

    /**
     * @brief Updates the game simulation.
     * @param deltaTime The time elapsed since the last update.
     * @param renderer The world renderer interface.
     */
    void update(float deltaTime, IWorldView& renderer) override;

    /**
     * @brief Renders the gameplay state.
     * @param renderer The world renderer interface.
     */
    void render(IWorldView& renderer) override;

    /**
     * @brief Checks if the game is over.
     * @return True if game is over, false otherwise.
     */
    bool isGameOver();

    /**
     * @brief Gets the game world.
     * @return Constant reference to the World.
     */
    [[nodiscard]] const World& getWorld() const { return *world; }

private:
    std::shared_ptr<IEntityFactory> factory; ///< Entity factory
    std::shared_ptr<World> world;            ///< The game world
    std::shared_ptr<Score> score;            ///< Score tracker

    bool playerWon = false;         ///< Indicates if the player won
    bool gameOverProcessed = false; ///< Indicates if game-over was processed
};

#endif // BOMBERMAN_PLAYSTATE_H
