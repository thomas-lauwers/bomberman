#ifndef BOMBERMAN_LOGIC_POWERUP_H
#define BOMBERMAN_LOGIC_POWERUP_H

#include "Entity.h"

namespace logic {

enum class PowerUpType {
    Fire,
    ExtraBomb,
    Skates
};

/**
 * @brief Represents a power-up dropped from a destroyed wall.
 */
class PowerUp : public Entity {
public:
    PowerUp(float x, float y, PowerUpType type);
    EntityType getType() const override { return EntityType::PowerUp; }
    void update() override;
    bool isAlive() const override;

    PowerUpType getPowerUpType() const;
    void collect();
    bool isCollected() const;

private:
    PowerUpType type;
    bool collected;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_POWERUP_H
