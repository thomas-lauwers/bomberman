#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "Bomber.h"

class Player : public Bomber {
public:
    Player();

    [[nodiscard]] EntityType getEntityType() const override;
    [[nodiscard]] BomberType getBomberType() const override;

private:
};

#endif // BOMBERMAN_PLAYER_H
