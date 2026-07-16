#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H
#include "Entity.h"

class Bomb : public Entity {
public:
    Bomb(float x, float y, int blast_radius);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;
    [[nodiscard]] int getBlastRadius() const;

    void update(float deltaTime) override;
    void explode();

private:
    Position position;
    float timer = 2.0f;
    int blast_radius;
};

#endif // BOMBERMAN_BOMB_H
