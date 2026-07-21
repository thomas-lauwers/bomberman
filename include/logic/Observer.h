/**
 * @file Observer.h
 * @brief Defines the Observer interface and event types for the Observer pattern.
 */

#ifndef BOMBERMAN_OBSERVER_H
#define BOMBERMAN_OBSERVER_H

class Entity;

/**
 * @enum Event
 * @brief Represents game events that can be observed.
 */
enum class Event {
    EntityDestroyed,       ///< Entity was destroyed
    BombExploded,          ///< Bomb exploded
    BomberMovedUp,         ///< Bomber moved up
    BomberMovedDown,       ///< Bomber moved down
    BomberMovedLeft,       ///< Bomber moved left
    BomberMovedRight,      ///< Bomber moved right
    BomberStopped,         ///< Bomber stopped moving
    PlayerBrokeBlock,      ///< Player broke a block
    PlayerPickedUpPowerUp, ///< Player picked up a power-up
    PlayerKilledEnemy,     ///< Player killed an enemy
    GameWon,               ///< Player won the game
    GameLost               ///< Player lost the game
};

/**
 * @class Observer
 * @brief Interface for objects that wish to observe game events.
 */
class Observer {
public:
    virtual ~Observer() = default;

    /**
     * @brief Called when a notified event occurs.
     * @param entity The entity that triggered the event.
     * @param event The type of event.
     */
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

#endif
