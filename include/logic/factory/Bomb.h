#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H
#include "Entity.h"


class Bomb : public Entity {
public:
    Bomb(float x, float y);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;

private:
    Position position;
};


#endif //BOMBERMAN_BOMB_H
