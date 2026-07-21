/**
 * @file WorldRenderer.h
 * @brief Defines the WorldRenderer class responsible for rendering the game world and its entities.
 */

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

/**
 * @class WorldRenderer
 * @brief Implementation of IWorldView that handles all rendering operations for the game world.
 */
class WorldRenderer : public IWorldView {
public:
    /**
     * @brief Constructs a WorldRenderer instance.
     * @param manager Reference to the TextureManager for asset access.
     * @param window Reference to the SFML render window.
     */
    WorldRenderer(TextureManager& manager, sf::RenderWindow& window);

    /**
     * @brief Gets the player's view observer.
     * @return Shared pointer to the PlayerView.
     */
    std::shared_ptr<PlayerView> getPlayerView() const;

    /**
     * @brief Loads all tile sprites from the TextureManager.
     */
    void loadTileSprites();

    /**
     * @brief Creates and registers a view for a bomb entity.
     * @param entity Pointer to the bomb entity.
     * @return Shared pointer to the BombView.
     */
    std::shared_ptr<BombView> createBombView(const Entity* entity);

    /**
     * @brief Creates and registers a view for an explosion entity.
     * @param entity Pointer to the explosion entity.
     * @return Shared pointer to the ExplosionView.
     */
    std::shared_ptr<ExplosionView> createExplosionView(const Entity* entity);

    /**
     * @brief Creates and registers a view for a crumbling wall entity.
     * @param entity Pointer to the crumbling wall entity.
     * @return Shared pointer to the CrumblingWallView.
     */
    std::shared_ptr<CrumblingWallView> createCrumblingWallView(const Entity* entity);

    /**
     * @brief Creates and registers a view for a power-up entity.
     * @param entity Pointer to the power-up entity.
     * @return Shared pointer to the PowerUpView.
     */
    std::shared_ptr<PowerUpView> createPowerUpView(const Entity* entity);

    /**
     * @brief Creates and registers a view for a knocked-out bomber entity.
     * @param entity Pointer to the bomber entity.
     * @param type The type of the bomber.
     * @return Shared pointer to the KnockedOutBomberView.
     */
    std::shared_ptr<KnockedOutBomberView> createKnockedOutBomberView(const Entity* entity, BomberType type);

    /**
     * @brief Creates and registers a view for an AI bomber entity.
     * @param entity Pointer to the AI bomber entity.
     * @param type The type of the bomber.
     * @return Shared pointer to the AIBomberView.
     */
    std::shared_ptr<AIBomberView> createAIBomberView(const Entity* entity, BomberType type);

    /**
     * @brief Renders the entire game world.
     * @param world Reference to the game world.
     */
    void render(const World& world) override;

    /**
     * @brief Renders centered text on the screen.
     * @param text The text to render.
     * @param y The Y coordinate.
     */
    void renderCenteredText(const std::string& text, float y) override;

    /**
     * @brief Renders text at a specific position on the screen.
     * @param text The text to render.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    void renderText(const std::string& text, float x, float y) override;

    /**
     * @brief Renders the player portrait at a specific position.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    void renderPortrait(float x, float y) override;

    /**
     * @brief Renders the title screen layout.
     * @param showEnter Whether to show the blinking "Press Z to Start" text.
     */
    void renderTitle(bool showEnter) override;

    /**
     * @brief Updates all entity views.
     * @param deltaTime Time elapsed since last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renders all tiles in the game world.
     * @param world Reference to the game world.
     */
    void renderTiles(const World& world);

    /**
     * @brief Renders non-bomber entities.
     * @param world Reference to the game world.
     */
    void renderNonBomberEntities(const World& world);

    /**
     * @brief Renders all bombers sorted by their position for correct layering.
     * @param world Reference to the game world.
     */
    void renderBombersSorted(const World& world);

    /**
     * @brief Removes views for entities that have been destroyed.
     * @param world Reference to the game world.
     */
    void removeDestroyedEntities(const World& world);

private:
    /**
     * @brief Helper to setup the UI coordinate system view.
     * @return The configured UI SFML view.
     */
    sf::View setupUIView() const;

    TextureManager& t_manager; ///< Reference to the texture manager
    sf::RenderWindow& window;  ///< Reference to the render window

    // Tile sprites
    sf::Sprite wall_sprite;         ///< Sprite for unbreakable walls
    sf::Sprite destructible_sprite; ///< Sprite for destructible walls
    sf::Sprite empty_sprite;        ///< Sprite for empty floor tiles
    sf::Sprite empty_shaded_sprite; ///< Sprite for shaded empty floor tiles

    // Entity views
    std::shared_ptr<PlayerView> p_view; ///< View for the player
    DestructibleWallView d_wall_view;   ///< View for destructible walls
    std::map<const Entity*, std::shared_ptr<CrumblingWallView>>
        c_wallViews;                                              ///< Map of crumbling wall entities to their views
    std::map<const Entity*, std::shared_ptr<BombView>> bombViews; ///< Map of bomb entities to their views
    std::map<const Entity*, std::shared_ptr<ExplosionView>>
        explosionViews;                                                 ///< Map of explosion entities to their views
    std::map<const Entity*, std::shared_ptr<PowerUpView>> powerupViews; ///< Map of power-up entities to their views
    std::map<const Entity*, std::shared_ptr<KnockedOutBomberView>>
        knockedoutbomberViews; ///< Map of knocked-out bomber entities to their views
    std::map<const Entity*, std::shared_ptr<AIBomberView>> aiBomberViews; ///< Map of AI bomber entities to their views
};

#endif // BOMBERMAN_WORLDRENDERER_H
