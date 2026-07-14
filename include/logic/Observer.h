#ifndef BOMBERMAN_OBSERVER_H
#define BOMBERMAN_OBSERVER_H

class Entity;

enum class Event {
    EntityDestroyed,
    BombExploded,
    PlayerMovedUp,
    PlayerMovedDown,
    PlayerMovedLeft,
    PlayerMovedRight,
    PlayerStopped
};

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

#endif
