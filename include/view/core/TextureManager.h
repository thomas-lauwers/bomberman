/**
 * @file TextureManager.h
 * @brief Defines the TextureManager class for loading and managing game assets (textures and fonts).
 */

#ifndef BOMBERMAN_TEXTUREMANAGER_H
#define BOMBERMAN_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <map>

/**
 * @class TextureManager
 * @brief Handles the loading, storage, and retrieval of textures and fonts used by the game.
 */
class TextureManager {
public:
    /**
     * @brief Constructs a TextureManager instance.
     */
    TextureManager();

    /**
     * @brief Loads all default game assets (textures).
     * @throws std::runtime_error If an essential asset fails to load.
     */
    void loadAssets();

    /**
     * @brief Loads a font from a file and registers it by name.
     * @param name The name to associate with the font.
     * @param filename The path to the font file.
     */
    void loadFont(const std::string& name, const std::string& filename);

    /**
     * @brief Retrieves a texture by its registered name.
     * @param name The name of the texture.
     * @return Constant reference to the requested sf::Texture.
     */
    [[nodiscard]] const sf::Texture& getTexture(const std::string& name) const;

    /**
     * @brief Retrieves a font by its registered name.
     * @param name The name of the font.
     * @return Constant reference to the requested sf::Font.
     */
    [[nodiscard]] const sf::Font& getFont(const std::string& name) const;

private:
    std::map<std::string, sf::Texture> textures; ///< Map of texture names to sf::Texture objects
    std::map<std::string, sf::Font> fonts;       ///< Map of font names to sf::Font objects
};

#endif // BOMBERMAN_TEXTUREMANAGER_H
