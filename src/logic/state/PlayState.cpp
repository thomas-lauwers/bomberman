#include <utility>

#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/IEntityFactory.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/state/PlayState.h"

PlayState::PlayState(std::shared_ptr<IEntityFactory> factory) : factory(std::move(factory)), world(this->factory) {}

void PlayState::handleInput(const Input input) {
    if (const auto player = world.getPlayer()) {
        float dx = 0.f;
        float dy = 0.f;

        switch (input) {
        case Input::MoveLeft:
            dx -= 1.f;
            break;
        case Input::MoveRight:
            dx += 1.f;
            break;
        case Input::MoveUp:
            dy -= 1.f;
            break;
        case Input::MoveDown:
            dy += 1.f;
            break;
        case Input::PlaceBomb:
            if (player->canPlaceBomb()) {
                auto bomb = factory->createBomb(player->getPosition().x, player->getPosition().y);
                player->setCanPlaceBomb(false);
                bomb->addObserver(player);

                const auto observer = std::make_shared<WorldObserver>(world);
                bomb->addObserver(observer);
                bombObservers.push_back(observer);

                world.pushBackEntity(std::move(bomb));
            }
            return;
        }

        if (dx != 0.f || dy != 0.f) {
            Rect initialRect = player->getCollisionRect();
            Position currentPos = player->getPosition();

            player->move(dx, dy);
            if (world.isColliding(player->getCollisionRect(), player.get(), initialRect)) {
                player->setPosition(currentPos.x, currentPos.y);
            } else {
                if (dx > 0)
                    player->triggerEvent(Event::PlayerMovedRight);
                else if (dx < 0)
                    player->triggerEvent(Event::PlayerMovedLeft);
                else if (dy > 0)
                    player->triggerEvent(Event::PlayerMovedDown);
                else if (dy < 0)
                    player->triggerEvent(Event::PlayerMovedUp);
            }
        }
    }
}

void PlayState::update(const float deltaTime, IWorldView& renderer) {
    renderer.update(deltaTime);
    if (const auto player = world.getPlayer()) {
        player->update(deltaTime);
    }
    for (auto& entity : world.getEntities()) {
        entity->update(deltaTime);
    }

    world.removeDestroyedEntities();
}

void PlayState::render(sf::RenderWindow& window, IWorldView& renderer) { renderer.render(window, world); }

PlayState::~PlayState() = default;
