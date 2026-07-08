#ifndef BOMBERMAN_LOGIC_ENTITY_H
#define BOMBERMAN_LOGIC_ENTITY_H

#include <vector>
#include <memory>
#include "Observer.h"

namespace logic {

enum class EntityType {
    Player,
    Enemy,
    Bomb,
    Wall,
    PowerUp,
    Explosion
};

/**
 * @brief Abstract base class for all game entities.
 * Coordinates are normalized [-1, 1].
 */
class Entity : public Subject {
public:
    Entity(float x, float y);
    virtual ~Entity() = default;

    virtual EntityType getType() const = 0;

    /**
     * @brief Update entity state for one tick.
     */
    virtual void update() = 0;
    virtual bool isAlive() const { return true; }
    virtual bool isSolid() const { return false; }
    virtual void getAABB(float& minX, float& minY, float& maxX, float& maxY) const;

    float getX() const { return x; }
    float getY() const { return y; }
    void setPosition(float nx, float ny) { x = nx; y = ny; notify(); }

    // Subject interface
    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    void notify() override;

protected:
    float x, y; // Normalized coordinates [-1, 1]
    std::vector<Observer*> observers;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_ENTITY_H
