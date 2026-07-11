#ifndef BOMBERMAN_WORLDRENDERER_H
#define BOMBERMAN_WORLDRENDERER_H

#include "../logic/World.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class WorldRenderer {
public:
    WorldRenderer();

    void loadAssets();
    void loadTileSprites();
    void loadPlayerSprites();

    void render(sf::RenderWindow& window, const World& world);
    void renderTiles(sf::RenderWindow& window, const World& world);
    void renderPlayer(sf::RenderWindow& window, const World& world);
    void renderEntities(sf::RenderWindow& window, const World& world);

private:
    TextureManager t_manager;

    // Tile sprites
    sf::Sprite wall_sprite;
    sf::Sprite destructible_sprite;
    sf::Sprite empty_sprite;
    sf::Sprite empty_shaded_sprite;

    // Entity sprites
    sf::Sprite player_sprite;
};


#endif //BOMBERMAN_WORLDRENDERER_H
