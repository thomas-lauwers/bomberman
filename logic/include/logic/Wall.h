#ifndef BOMBERMAN_LOGIC_WALL_H
#define BOMBERMAN_LOGIC_WALL_H

#include "Entity.h"

namespace logic {

/**
 * @brief Represents a wall in the arena.
 */
class Wall : public Entity {
public:
    Wall(float x, float y, bool destructible);
    EntityType getType() const override { return EntityType::Wall; }
    void update() override;
    bool isAlive() const override;
    bool isSolid() const override { return true; }

    bool isDestructible() const;
    void destroy();
    bool isDestroyed() const;

private:
    bool destructible;
    bool destroyed;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_WALL_H
