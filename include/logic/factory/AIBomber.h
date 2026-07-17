#ifndef BOMBERMAN_AIBOMBER_H
#define BOMBERMAN_AIBOMBER_H

#include "Bomber.h"
#include "BomberType.h"

class AIBomber : public Bomber {
public:
    explicit AIBomber(BomberType type);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] BomberType getBomberType() const override;
    [[nodiscard]] BomberType getType() const { return type; }

    void update(float deltaTime) override;

private:
    BomberType type;
};

#endif // BOMBERMAN_AIBOMBER_H
