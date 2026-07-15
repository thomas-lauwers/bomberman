#ifndef BOMBERMAN_COLLIDABLE_H
#define BOMBERMAN_COLLIDABLE_H
#include "../Rect.h"
#include "../../utils/Position.h"
#include "../Subject.h"

enum EntityType {
    Player_E,
    DestructibleWall_E,
    CrumblingWall_E,
    Bomb_E,
    Explosion_E
};

class Entity : public Subject {
public:
    ~Entity() override = default;

    [[nodiscard]] virtual EntityType getEntityType() const = 0;
    [[nodiscard]] virtual Position getPosition() const = 0;
    [[nodiscard]] virtual Rect getCollisionRect() const = 0;

    [[nodiscard]] bool isDestroyed() const { return destroyed; }
    void destroy() {
        destroyed = true;
        notify(*this, Event::EntityDestroyed);
    }

    virtual void update(float deltaTime) {}

protected:
    bool destroyed = false;
};


#endif //BOMBERMAN_COLLIDABLE_H
