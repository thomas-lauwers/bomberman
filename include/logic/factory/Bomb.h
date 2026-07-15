#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H
#include "Entity.h"


class Bomb : public Entity {
public:
    Bomb(float x, float y);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;

    void update(float deltaTime) override;
    void tick();
    void explode();

private:
    Position position;
    float timer = 2.0f;
};


#endif //BOMBERMAN_BOMB_H
