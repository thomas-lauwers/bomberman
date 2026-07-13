#ifndef BOMBERMAN_BATTLESTAGEFACTORY_H
#define BOMBERMAN_BATTLESTAGEFACTORY_H

#include "../../logic/factory/IEntityFactory.h"
#include "../TextureManager.h"

class BattleStageFactory : public IEntityFactory {
public:
    explicit BattleStageFactory(const TextureManager& t_manager) : textureManager(t_manager) {}

    std::unique_ptr<Player> createPlayer() override;
    std::unique_ptr<Bomb> createBomb(float x, float y) override;
    std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) override;
    std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) override;

private:
    const TextureManager& textureManager;
};


#endif //BOMBERMAN_BATTLESTAGEFACTORY_H
