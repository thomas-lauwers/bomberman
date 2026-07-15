#ifndef BOMBERMAN_EXPLOSION_H
#define BOMBERMAN_EXPLOSION_H
#include "Entity.h"

enum class ExplosionType {
    Center,
    Horizontal,
    Vertical,
    EndUp,
    EndDown,
    EndLeft,
    EndRight
};

class Explosion : public Entity {
public:
    Explosion(float x, float y, ExplosionType type);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;
    [[nodiscard]] ExplosionType getType() const;

    void update(float deltaTime) override;

private:
    Position position;
    ExplosionType type;
    float lifetime = 0.6f;
};


#endif //BOMBERMAN_EXPLOSION_H
