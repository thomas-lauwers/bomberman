#ifndef BOMBERMAN_AIBOMBER_H
#define BOMBERMAN_AIBOMBER_H

#include "Bomber.h"

enum class AIBomberType { Variant1, Variant2, Variant3 };

class AIBomber : public Bomber {
public:
    explicit AIBomber(AIBomberType type);

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] AIBomberType getType() const { return type; }

    void update(float deltaTime) override;

private:
    AIBomberType type;
};

#endif // BOMBERMAN_AIBOMBER_H
