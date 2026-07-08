#ifndef BOMBERMAN_LOGIC_BOMB_H
#define BOMBERMAN_LOGIC_BOMB_H

#include "Entity.h"

namespace logic {

/**
 * @brief Represents a bomb placed by a player or enemy.
 */
class Bomb : public Entity {
public:
    Bomb(float x, float y, int range);
    EntityType getType() const override { return EntityType::Bomb; }
    void update() override;
    bool isAlive() const override;
    bool isSolid() const override { return true; }

    bool hasExploded() const;
    bool wereExplosionsSpawned() const;
    void setExplosionsSpawned();
    int getRange() const;
    void trigger(); // Immediate explosion (e.g., from another explosion)

private:
    int range;
    float timer;
    bool exploded;
    bool explosionsSpawned;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_BOMB_H
