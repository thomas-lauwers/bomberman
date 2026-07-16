#ifndef BOMBERMAN_WORLDRENDERER_H
#define BOMBERMAN_WORLDRENDERER_H

#include "../../logic/IWorldView.h"
#include "../../logic/factory/Entity.h"
#include "../core/TextureManager.h"
#include "../entities/BombView.h"
#include "../entities/CrumblingWallView.h"
#include "../entities/DestructibleWallView.h"
#include "../entities/ExplosionView.h"
#include "../entities/PlayerView.h"
#include "../entities/PowerUpView.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class WorldRenderer : public IWorldView {
public:
    explicit WorldRenderer(TextureManager& manager);
    std::shared_ptr<PlayerView> getPlayerView() const;

    void loadTileSprites();

    void render(sf::RenderWindow& window, const World& world) override;
    void update(float deltaTime) override;
    void renderTiles(sf::RenderWindow& window, const World& world);
    void renderPlayer(sf::RenderWindow& window, const World& world) const;
    void renderEntities(sf::RenderWindow& window, const World& world);

    void removeDestroyedEntities(const World& world);

private:
    TextureManager& t_manager;

    // Tile sprites
    sf::Sprite wall_sprite;
    sf::Sprite destructible_sprite;
    sf::Sprite empty_sprite;
    sf::Sprite empty_shaded_sprite;

    // Entity views
    std::shared_ptr<PlayerView> p_view;
    DestructibleWallView d_wall_view;
    std::map<const Entity*, std::unique_ptr<CrumblingWallView>> c_wallViews;
    std::map<const Entity*, std::unique_ptr<BombView>> bombViews;
    std::map<const Entity*, std::unique_ptr<ExplosionView>> explosionViews;
    std::map<const Entity*, std::unique_ptr<PowerUpView>> powerupViews;
};

#endif // BOMBERMAN_WORLDRENDERER_H
