#ifndef BOMBERMAN_POWERUP_H
#define BOMBERMAN_POWERUP_H
#include "Entity.h"
#include "../../utils/Position.h"

enum PowerUpType { Fire, ExtraBomb, Skates };

class PowerUp : public Entity  {
public:
    PowerUp(float x, float y);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] Position getPosition() const override;
    [[nodiscard]] Rect getCollisionRect() const override;
    [[nodiscard]] PowerUpType getType() const;

private:
    Position position;
    PowerUpType type;
};


#endif //BOMBERMAN_POWERUP_H
