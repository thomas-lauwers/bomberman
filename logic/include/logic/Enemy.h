#ifndef BOMBERMAN_LOGIC_ENEMY_H
#define BOMBERMAN_LOGIC_ENEMY_H

#include "Entity.h"

namespace logic {

/**
 * @brief Represents an AI-controlled enemy bot.
 */
class Enemy : public Entity {
public:
    Enemy(float x, float y, int behaviorType);
    EntityType getType() const override { return EntityType::Enemy; }
    void update() override;
    bool isAlive() const override;
    void kill();

    void performAI(class World& world);

private:
    int behaviorType; // Different behaviors: flee, collect, attack
    bool dead;
    int moveCounter;
    float curDx, curDy;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_ENEMY_H
