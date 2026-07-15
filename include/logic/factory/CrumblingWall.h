#ifndef BOMBERMAN_CRUMBLINGWALL_H
#define BOMBERMAN_CRUMBLINGWALL_H
#include "Entity.h"

class CrumblingWall : public Entity {
public:
    CrumblingWall(float x, float y);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;

    void update(float deltaTime) override;

private:
    Position position;
    float lifetime = 0.75f;
};


#endif //BOMBERMAN_CRUMBLINGWALL_H
