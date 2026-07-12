#ifndef BOMBERMAN_COLLIDABLE_H
#define BOMBERMAN_COLLIDABLE_H
#include "../Rect.h"
#include "../../utils/Position.h"

enum EntityType {
    Player_E,
    DestructibleWall_E,
    Bomb_E
};

class Entity {
public:
    virtual ~Entity() = default;

    [[nodiscard]] virtual EntityType getEntityType() const = 0;
    [[nodiscard]] virtual Position getPosition() const = 0;
    [[nodiscard]] virtual Rect getCollisionRect() const = 0;

    [[nodiscard]] bool isDestroyed() const { return destroyed; }
    void destroy() { destroyed = true; }

    virtual void update() {}

protected:
    bool destroyed = false;
};


#endif //BOMBERMAN_COLLIDABLE_H
