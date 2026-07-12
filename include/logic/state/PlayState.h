#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H

#include "../../view/WorldRenderer.h"
#include "State.h"
#include "../World.h"
#include <SFML/Graphics.hpp>
#include <memory>

class IEntityFactory;

class PlayState : public State {
public:
    explicit PlayState(std::shared_ptr<IEntityFactory> factory);

    void handleInput() override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    std::shared_ptr<IEntityFactory> factory;
    World world;
    WorldRenderer renderer;
};


#endif //BOMBERMAN_PLAYSTATE_H
