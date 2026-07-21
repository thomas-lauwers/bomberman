/**
 * @file BomberType.h
 * @brief Defines the BomberType enum for different types of bombers.
 */

#ifndef BOMBERMAN_BOMBERTYPE_H
#define BOMBERMAN_BOMBERTYPE_H

/**
 * @enum BomberType
 * @brief Represents the types of bombers available in the game.
 */
enum class BomberType { 
    Player,   ///< The player-controlled bomber
    Variant1, ///< AI Variant 1
    Variant2, ///< AI Variant 2
    Variant3  ///< AI Variant 3
};

#endif // BOMBERMAN_BOMBERTYPE_H
