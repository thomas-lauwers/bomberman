#ifndef BOMBERMAN_REP_STATE_MANAGER_H
#define BOMBERMAN_REP_STATE_MANAGER_H

namespace rep {

enum class GameState {
    StartScreen,
    Gameplay,
    GameOver
};

/**
 * @brief Manages the different states of the game (menu, playing, game over).
 */
class StateManager {
public:
    StateManager();

    void setState(GameState newState);
    GameState getState() const;

private:
    GameState currentState;
};

} // namespace rep

#endif // BOMBERMAN_REP_STATE_MANAGER_H
