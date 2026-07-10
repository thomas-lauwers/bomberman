#ifndef BOMBERMAN_WORLDRENDERER_H
#define BOMBERMAN_WORLDRENDERER_H

#include "../logic/World.h"
#include <SFML/Graphics.hpp>

class WorldRenderer {
public:
    WorldRenderer();

    void loadAssets();
    void render(sf::RenderWindow& window, const World& world);
    void renderTiles(sf::RenderWindow& window, const World& world);
    void renderPlayer(sf::RenderWindow& window, const World& world);

private:
    sf::Texture wall;
    sf::Texture destructible;
    sf::Texture empty;
    sf::Texture empty_shaded;

    sf::Sprite wall_sprite;
    sf::Sprite destructible_sprite;
    sf::Sprite empty_sprite;
    sf::Sprite empty_shaded_sprite;

    sf::Texture player;

    sf::Sprite player_sprite;
};


#endif //BOMBERMAN_WORLDRENDERER_H
