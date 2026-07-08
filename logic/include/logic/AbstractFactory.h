#ifndef BOMBERMAN_LOGIC_ABSTRACT_FACTORY_H
#define BOMBERMAN_LOGIC_ABSTRACT_FACTORY_H

#include <memory>

namespace logic {

class Player;
class Enemy;
class Bomb;
class Wall;
class PowerUp;
class Explosion;

/**
 * @brief Abstract Factory interface for creating game entities.
 */
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

    virtual std::shared_ptr<Player> createPlayer(float x, float y) = 0;
    virtual std::shared_ptr<Enemy> createEnemy(float x, float y, int type) = 0;
    virtual std::shared_ptr<Bomb> createBomb(float x, float y, int range) = 0;
    virtual std::shared_ptr<Wall> createWall(float x, float y, bool destructible) = 0;
    virtual std::shared_ptr<PowerUp> createPowerUp(float x, float y, int type) = 0;
    virtual std::shared_ptr<Explosion> createExplosion(float x, float y) = 0;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_ABSTRACT_FACTORY_H
