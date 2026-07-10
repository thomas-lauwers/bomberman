#ifndef BOMBERMAN_BATTLESTAGEFACTORY_H
#define BOMBERMAN_BATTLESTAGEFACTORY_H

#include "IEntityFactory.h"

class BattleStageFactory : public IEntityFactory {
public:
    std::unique_ptr<Player> createPlayer() override;
};


#endif //BOMBERMAN_BATTLESTAGEFACTORY_H
