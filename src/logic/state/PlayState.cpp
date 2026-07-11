#include "../../../include/logic/state/PlayState.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/IEntityFactory.h"
#include "../../../include/logic/factory/Player.h"


PlayState::PlayState(std::unique_ptr<IEntityFactory> factory) : factory(std::move(factory)) {
    world.setPlayer(this->factory->createPlayer());
}

void PlayState::handleInput() {
    if (auto* player = world.getPlayer()) {
        float dx = 0.f;
        float dy = 0.f;
        Position initialPos = player->getPosition();
        Rect initialRect = player->getCollisionRect();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) dx -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) dx += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) dy -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) dy += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) world.pushBackEntity(factory->createBomb(initialPos.x, initialPos.y));

        if (dx != 0.f || dy != 0.f) {
            Position currentPos = player->getPosition();
            // Try moving in X
            player->move(dx, 0.f);
            if (world.isColliding(player->getCollisionRect(), player, initialRect)) {
                player->setPosition(currentPos.x, currentPos.y);
            } else {
                currentPos.x = player->getPosition().x;
            }

            // Try moving in Y
            player->move(0.f, dy);
            if (world.isColliding(player->getCollisionRect(), player, initialRect)) {
                player->setPosition(currentPos.x, currentPos.y);
            }
        }
    }
}
void PlayState::update() {}
void PlayState::render(sf::RenderWindow& window) {
    renderer.render(window, world);
}
