#ifndef BOMBERMAN_TEXTUREMANAGER_H
#define BOMBERMAN_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {
public:
    TextureManager();

    void loadAssets();
    void loadFont(const std::string& name, const std::string& filename);

    [[nodiscard]] const sf::Texture& getTexture(const std::string& name) const;
    [[nodiscard]] const sf::Font& getFont(const std::string& name) const;

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};

#endif // BOMBERMAN_TEXTUREMANAGER_H
