#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "../../utils/Position.h"
#include "../Observer.h"
#include "../Rect.h"
#include "Entity.h"

class Player : public Entity, public Observer {
public:
    Player();

    [[nodiscard]] EntityType getEntityType() const override;

    void setPosition(float x, float y);
    [[nodiscard]] Position getPosition() const override;

    void move(float dx, float dy);

    [[nodiscard]] Rect getCollisionRect() const override;

    void onNotify(const Entity& entity, Event event) override;

    [[nodiscard]] bool canPlaceBomb() const;

    void setCanPlaceBomb(bool can);

    void triggerEvent(Event event);

    void update(float deltaTime) override;

private:
    Position position{1.0f, 1.0f};
    float speed = 4.0f; // units per second
    bool canPlace = true;
    bool isMoving = false;
    bool wasMoving = false;
};

#endif // BOMBERMAN_PLAYER_H
