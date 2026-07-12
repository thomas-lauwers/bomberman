#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "Entity.h"
#include "../Observer.h"
#include "../../utils/Position.h"
#include "../Rect.h"

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

private:
    Position position{1.0f, 1.0f};
    float speed = 3.0f; // units per second
    bool canPlace = true;
};


#endif //BOMBERMAN_PLAYER_H
