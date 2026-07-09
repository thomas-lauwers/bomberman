#include "../../include/logic/PlayState.h"

PlayState::PlayState() = default;

void PlayState::handleInput() {}
void PlayState::update() {}
void PlayState::render(sf::RenderWindow& window) {
    renderer.render(window, world);
}
