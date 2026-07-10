#ifndef BOMBERMAN_TEXTUREMANAGER_H
#define BOMBERMAN_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {
public:
    TextureManager();

    void loadAssets();

    [[nodiscard]] const sf::Texture& getTexture(const std::string& name) const;

private:
    std::map<std::string, sf::Texture> textures;
};


#endif //BOMBERMAN_TEXTUREMANAGER_H
