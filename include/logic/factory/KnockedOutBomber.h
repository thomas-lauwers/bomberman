#ifndef BOMBERMAN_KNOCKEDOUTBOMBER_H
#define BOMBERMAN_KNOCKEDOUTBOMBER_H

#include "Entity.h"
#include "AIBomber.h"

class KnockedOutBomber : public Entity {
public:
    KnockedOutBomber(float x, float y, BomberType type);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;
    [[nodiscard]] BomberType getBomberType() const { return type; }

    void update(float deltaTime) override;

private:
    Position position;
    BomberType type;
    float lifetime = 2.0f;
};


#endif //BOMBERMAN_KNOCKEDOUTBOMBER_H
