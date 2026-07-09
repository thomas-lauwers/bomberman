#ifndef BOMBERMAN_WORLDRENDERER_H
#define BOMBERMAN_WORLDRENDERER_H

#include "../logic/World.h"
#include <SFML/Graphics.hpp>

class WorldRenderer {
public:
    WorldRenderer();

    void loadAssets();
    void render(sf::RenderWindow& window, const World& world) const;

private:
    sf::Texture wall;
    sf::Texture destructible;
    sf::Texture empty;

    sf::Sprite wall_sprite;
    sf::Sprite destructible_sprite;
    sf::Sprite empty_sprite;
};


#endif //BOMBERMAN_WORLDRENDERER_H
