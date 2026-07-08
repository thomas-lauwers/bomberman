#ifndef BOMBERMAN_LOGIC_EXPLOSION_H
#define BOMBERMAN_LOGIC_EXPLOSION_H

#include "Entity.h"

namespace logic {

/**
 * @brief Represents an explosion effect in the arena.
 */
class Explosion : public Entity {
public:
    Explosion(float x, float y);
    EntityType getType() const override { return EntityType::Explosion; }
    void update() override;
    bool isAlive() const override;

    bool isFinished() const;

private:
    float timer;
    bool finished;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_EXPLOSION_H
