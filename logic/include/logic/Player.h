#ifndef BOMBERMAN_LOGIC_PLAYER_H
#define BOMBERMAN_LOGIC_PLAYER_H

#include "Entity.h"

namespace logic {

/**
 * @brief Represents the human-controlled player.
 */
class Player : public Entity {
public:
    Player(float x, float y);
    EntityType getType() const override { return EntityType::Player; }
    void update() override;
    bool isAlive() const override;

    void move(float dx, float dy);
    bool canPlaceBomb() const;
    void placeBomb();
    void onBombExploded();

    // Power-up effects
    void increaseRange();
    void increaseBombCapacity();
    void increaseSpeed();
    void kill();

private:
    float speed;
    int bombRange;
    int bombCapacity;
    int activeBombs;
    bool dead;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_PLAYER_H
