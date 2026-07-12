#ifndef BOMBERMAN_WORLDRENDERER_H
#define BOMBERMAN_WORLDRENDERER_H

#include "../logic/IWorldView.h"
#include "TextureManager.h"
#include "PlayerView.h"
#include "DestructibleWallView.h"
#include "BombView.h"
#include <SFML/Graphics.hpp>


class WorldRenderer : public IWorldView {
public:
    explicit WorldRenderer(TextureManager& manager);

    void loadTileSprites();

    void render(sf::RenderWindow& window, const World& world) override;
    void renderTiles(sf::RenderWindow& window, const World& world);
    void renderPlayer(sf::RenderWindow& window, const World& world);
    void renderEntities(sf::RenderWindow& window, const World& world);

private:
    TextureManager& t_manager;

    // Tile sprites
    sf::Sprite wall_sprite;
    sf::Sprite destructible_sprite;
    sf::Sprite empty_sprite;
    sf::Sprite empty_shaded_sprite;

    // Entity views
    PlayerView p_view;
    DestructibleWallView d_wall_view;
    BombView b_view;
};


#endif //BOMBERMAN_WORLDRENDERER_H
