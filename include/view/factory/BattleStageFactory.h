#ifndef BOMBERMAN_BATTLESTAGEFACTORY_H
#define BOMBERMAN_BATTLESTAGEFACTORY_H

#include "../../logic/factory/IEntityFactory.h"
#include "../core/TextureManager.h"
#include "../entities/PlayerView.h"
#include <memory>

class BattleStageFactory : public IEntityFactory {
public:
    explicit BattleStageFactory(const TextureManager& t_manager) : textureManager(t_manager) {}

    void setPlayerView(std::shared_ptr<PlayerView> view);
    std::unique_ptr<Player> createPlayer() override;
    std::unique_ptr<Bomb> createBomb(float x, float y) override;
    std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) override;
    std::unique_ptr<Explosion> createExplosion(float x, float y, ExplosionType type) override;
    std::unique_ptr<CrumblingWall> createCrumblingWall(float x, float y) override;

private:
    const TextureManager& textureManager;
    std::shared_ptr<PlayerView> playerView;
};

#endif // BOMBERMAN_BATTLESTAGEFACTORY_H
