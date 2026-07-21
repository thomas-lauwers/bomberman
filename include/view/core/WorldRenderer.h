#ifndef BOMBERMAN_WORLDRENDERER_H
#define BOMBERMAN_WORLDRENDERER_H

#include "../../logic/IWorldView.h"
#include "../../logic/factory/Entity.h"
#include "../core/TextureManager.h"
#include "../entities/AIBomberView.h"
#include "../entities/BombView.h"
#include "../entities/CrumblingWallView.h"
#include "../entities/DestructibleWallView.h"
#include "../entities/ExplosionView.h"
#include "../entities/KnockedOutBomberView.h"
#include "../entities/PlayerView.h"
#include "../entities/PowerUpView.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class WorldRenderer : public IWorldView {
public:
    WorldRenderer(TextureManager& manager, sf::RenderWindow& window);
    std::shared_ptr<PlayerView> getPlayerView() const;

    void loadTileSprites();

    std::shared_ptr<BombView> createBombView(const Entity* entity);
    std::shared_ptr<ExplosionView> createExplosionView(const Entity* entity);
    std::shared_ptr<CrumblingWallView> createCrumblingWallView(const Entity* entity);
    std::shared_ptr<PowerUpView> createPowerUpView(const Entity* entity);
    std::shared_ptr<KnockedOutBomberView> createKnockedOutBomberView(const Entity* entity, BomberType type);
    std::shared_ptr<AIBomberView> createAIBomberView(const Entity* entity, BomberType type);

    void render(const World& world) override;
    void renderCenteredText(const std::string& text, float y) override;
    void renderText(const std::string& text, float x, float y) override;
    void renderPortrait(float x, float y) override;
    void renderTitle(bool showEnter) override;
    void update(float deltaTime) override;
    void renderTiles(const World& world);
    void renderNonBomberEntities(const World& world);
    void renderBombersSorted(const World& world);

    void removeDestroyedEntities(const World& world);

private:
    sf::View setupUIView() const;
    TextureManager& t_manager;
    sf::RenderWindow& window;

    // Tile sprites
    sf::Sprite wall_sprite;
    sf::Sprite destructible_sprite;
    sf::Sprite empty_sprite;
    sf::Sprite empty_shaded_sprite;

    // Entity views
    std::shared_ptr<PlayerView> p_view;
    DestructibleWallView d_wall_view;
    std::map<const Entity*, std::shared_ptr<CrumblingWallView>> c_wallViews;
    std::map<const Entity*, std::shared_ptr<BombView>> bombViews;
    std::map<const Entity*, std::shared_ptr<ExplosionView>> explosionViews;
    std::map<const Entity*, std::shared_ptr<PowerUpView>> powerupViews;
    std::map<const Entity*, std::shared_ptr<KnockedOutBomberView>> knockedoutbomberViews;
    std::map<const Entity*, std::shared_ptr<AIBomberView>> aiBomberViews;
};

#endif // BOMBERMAN_WORLDRENDERER_H
