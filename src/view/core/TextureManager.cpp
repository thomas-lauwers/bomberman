#include "../../../include/view/core/TextureManager.h"
#include <stdexcept>
#include <string>
#include <vector>

TextureManager::TextureManager() { loadAssets(); }

void TextureManager::loadAssets() {
    struct AssetInfo {
        std::string key;
        std::string filename;
    };
    const std::vector<AssetInfo> assets = {{"battle_stage_sprites", "assets/battle_stage_sprites.png"},
                                           {"character_sprites", "assets/character_sprites.png"},
                                           {"portrait", "assets/portrait.png"},
                                           {"powerup_sprites", "assets/powerup_sprites.png"}};

    for (const auto& [key, filename] : assets) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load: " + filename);
        }
        textures.emplace(key, std::move(texture));
    }
}

void TextureManager::loadFont(const std::string& name, const std::string& filename) {
    sf::Font font;
    if (!font.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load font: " + filename);
    }
    fonts.emplace(name, std::move(font));
}

const sf::Texture& TextureManager::getTexture(const std::string& name) const { return textures.at(name); }
const sf::Font& TextureManager::getFont(const std::string& name) const { return fonts.at(name); }
