#include "../../../include/logic/state/PlayState.h"

#include "../../../include/logic/factory/IEntityFactory.h"
#include "../../../include/logic/factory/Player.h"


PlayState::PlayState(std::unique_ptr<IEntityFactory> factory) : factory(std::move(factory)) {
    world.setPlayer(this->factory->createPlayer());
}

void PlayState::handleInput() {}
void PlayState::update() {}
void PlayState::render(sf::RenderWindow& window) {
    renderer.render(window, world);
}
