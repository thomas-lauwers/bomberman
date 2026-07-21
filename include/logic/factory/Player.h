/**
 * @file Player.h
 * @brief Defines the Player class for the human-controlled bomber.
 */

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "Bomber.h"

/**
 * @class Player
 * @brief Represents the player-controlled bomber entity.
 */
class Player : public Bomber {
public:
    /**
     * @brief Constructs a Player instance.
     */
    Player();

    /**
     * @brief Gets the entity type.
     * @return EntityType::Player_E.
     */
    [[nodiscard]] EntityType getEntityType() const override;

    /**
     * @brief Gets the bomber type.
     * @return BomberType::Player.
     */
    [[nodiscard]] BomberType getBomberType() const override;
};

#endif // BOMBERMAN_PLAYER_H
