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
    explicit PlayState(std::unique_ptr<IEntityFactory> factory);

    void handleInput() override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    World world;
    WorldRenderer renderer;
    std::unique_ptr<IEntityFactory> factory;
};


#endif //BOMBERMAN_PLAYSTATE_H
