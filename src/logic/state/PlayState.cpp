#include <utility>

#include "../../../include/logic/state/PlayState.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/IEntityFactory.h"
#include "../../../include/logic/factory/Player.h"


PlayState::PlayState(std::shared_ptr<IEntityFactory> factory) 
    : factory(std::move(factory)), world(this->factory) {
}

void PlayState::handleInput(const Input input) {
    if (auto* player = world.getPlayer()) {
        float dx = 0.f;
        float dy = 0.f;

        switch (input) {
            case Input::MoveLeft: dx -= 1.f; break;
            case Input::MoveRight: dx += 1.f; break;
            case Input::MoveUp: dy -= 1.f; break;
            case Input::MoveDown: dy += 1.f; break;
            case Input::PlaceBomb:
                world.pushBackEntity(factory->createBomb(player->getPosition().x, player->getPosition().y));
                return;
        }

        if (dx != 0.f || dy != 0.f) {
            Rect initialRect = player->getCollisionRect();
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

void PlayState::update() {
    for (auto& entity : world.getEntities()) {
        entity->update();
    }

    world.removeDestroyedEntities();
}

void PlayState::render(sf::RenderWindow& window) {
    renderer.render(window, world);
}
