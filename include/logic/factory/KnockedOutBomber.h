#ifndef BOMBERMAN_KNOCKEDOUTBOMBER_H
#define BOMBERMAN_KNOCKEDOUTBOMBER_H

#include "Entity.h"

class KnockedOutBomber : public Entity {
public:
    KnockedOutBomber(float x, float y);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;

    void update(float deltaTime) override;

private:
    Position position;
    float lifetime = 2.0f;
};


#endif //BOMBERMAN_KNOCKEDOUTBOMBER_H
