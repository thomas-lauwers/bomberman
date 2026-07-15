#include "../../../include/view/core/TextureManager.h"

TextureManager::TextureManager() {
    loadAssets();
}

void TextureManager::loadAssets() {
    if (sf::Texture battleTexture; battleTexture.loadFromFile("assets/battle_stage_sprites.png")) {
        textures.emplace("battle_stage_sprites", std::move(battleTexture));
    }

    if (sf::Texture characterTexture; characterTexture.loadFromFile("assets/character_sprites.png")) {
        textures.emplace("character_sprites", std::move(characterTexture));
    }

    if (sf::Texture powerupTexture; powerupTexture.loadFromFile("assets/powerup_sprites.png")) {
        textures.emplace("powerup_sprites", std::move(powerupTexture));
    }
}

const sf::Texture & TextureManager::getTexture(const std::string &name) const {
    return textures.at(name);
}
