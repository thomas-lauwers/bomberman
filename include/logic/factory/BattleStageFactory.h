#ifndef BOMBERMAN_BATTLESTAGEFACTORY_H
#define BOMBERMAN_BATTLESTAGEFACTORY_H

#include "IEntityFactory.h"

class BattleStageFactory : public IEntityFactory {
public:
    std::unique_ptr<Player> createPlayer() override;
    std::unique_ptr<Bomb> createBomb(float x, float y) override;
    std::unique_ptr<DestructibleWall> createDestructibleWall(float x, float y) override;
};


#endif //BOMBERMAN_BATTLESTAGEFACTORY_H
