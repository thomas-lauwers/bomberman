#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H
#include "State.h"
#include "Arena.h"
#include <SFML/Graphics.hpp>

class PlayState : public State {
public:
    PlayState();

    void handleInput() override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Arena arena;
};


#endif //BOMBERMAN_PLAYSTATE_H
