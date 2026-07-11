#ifndef BOMBERMAN_DESTRUCTIBLEWALL_H
#define BOMBERMAN_DESTRUCTIBLEWALL_H
#include "Entity.h"
#include "../../utils/Position.h"


class DestructibleWall : public Entity {
public:
    DestructibleWall(float x, float y);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;

private:
    Position position;
};


#endif //BOMBERMAN_DESTRUCTIBLEWALL_H
