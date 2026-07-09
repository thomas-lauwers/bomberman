#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H

#include "../view/WorldRenderer.h"
#include "State.h"
#include "World.h"
#include <SFML/Graphics.hpp>

class PlayState : public State {
public:
    PlayState();

    void handleInput() override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    World world;
    WorldRenderer renderer;
};


#endif //BOMBERMAN_PLAYSTATE_H
