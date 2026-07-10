#include "../../../include/logic/state/PlayState.h"

#include "../../../include/logic/factory/IEntityFactory.h"
#include "../../../include/logic/factory/Player.h"


PlayState::PlayState(std::unique_ptr<IEntityFactory> factory) : factory(std::move(factory)) {
    world.setPlayer(this->factory->createPlayer());
}

void PlayState::handleInput() {
    if (auto* player = world.getPlayer()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
            player->move(-1.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            player->move(1.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            player->move(0.f, -1.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            player->move(0.f, 1.f);
        }
    }
}
void PlayState::update() {}
void PlayState::render(sf::RenderWindow& window) {
    renderer.render(window, world);
}
