#ifndef BOMBERMAN_IENTITYFACTORY_H
#define BOMBERMAN_IENTITYFACTORY_H

#include <memory>

class Player;

class IEntityFactory {
public:
    virtual ~IEntityFactory() = default;

    virtual std::unique_ptr<Player> createPlayer() = 0;
};


#endif //BOMBERMAN_IENTITYFACTORY_H
