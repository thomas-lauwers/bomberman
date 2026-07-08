#ifndef BOMBERMAN_REP_CONCRETE_FACTORY_H
#define BOMBERMAN_REP_CONCRETE_FACTORY_H

#include "logic/AbstractFactory.h"
#include "View.h"
#include <vector>
#include <memory>

namespace rep {

/**
 * @brief Concrete implementation of AbstractFactory that also creates SFML Views.
 */
class ConcreteFactory : public logic::AbstractFactory {
public:
    ConcreteFactory();

    std::shared_ptr<logic::Player> createPlayer(float x, float y) override;
    std::shared_ptr<logic::Enemy> createEnemy(float x, float y, int type) override;
    std::shared_ptr<logic::Bomb> createBomb(float x, float y, int range) override;
    std::shared_ptr<logic::Wall> createWall(float x, float y, bool destructible) override;
    std::shared_ptr<logic::PowerUp> createPowerUp(float x, float y, int type) override;
    std::shared_ptr<logic::Explosion> createExplosion(float x, float y) override;

    /**
     * @brief Get all created views to be drawn.
     */
    const std::vector<std::shared_ptr<View>>& getViews() const;

    void cleanup();

private:
    std::vector<std::shared_ptr<View>> views;
};

} // namespace rep

#endif // BOMBERMAN_REP_CONCRETE_FACTORY_H
