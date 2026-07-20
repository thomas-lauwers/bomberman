#include <utility>

#include "../../../include/logic/factory/AIBomber.h"
#include "../../../include/logic/factory/Bomb.h"
#include "../../../include/logic/factory/IEntityFactory.h"
#include "../../../include/logic/factory/Player.h"
#include "../../../include/logic/state/PlayState.h"

PlayState::PlayState(std::shared_ptr<IEntityFactory> factory)
    : factory(std::move(factory)), world(std::make_shared<World>(this->factory)) {
    if (const auto player = world->getPlayer()) {
        player->addObserver(world);
    }
    for (const auto& entity : world->getEntities()) {
        if (entity->getEntityType() == AIBomber_E) {
            entity->addObserver(world);
        }
    }
}

void PlayState::handleInput(const Input input) {
    if (const auto player = world->getPlayer()) {
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
            if (player->canPlaceBomb() && !world->isBombAt(player->getPosition().x, player->getPosition().y)) {
                auto bomb =
                    factory->createBomb(player->getPosition().x, player->getPosition().y, player->getBlastRadius());
                player->placeBomb();
                bomb->addObserver(player);
                bomb->addObserver(world);

                world->pushBackEntity(std::move(bomb));
            }
            return;
        case Input::Select:
            return;
        }

        if (dx != 0.f || dy != 0.f) {
            Rect initialRect = player->getCollisionRect();
            Position currentPos = player->getPosition();

            player->move(dx, dy);
            if (world->isColliding(player->getCollisionRect(), player.get(), initialRect)) {
                player->setPosition(currentPos.x, currentPos.y);
            } else {
                if (dx > 0)
                    player->triggerEvent(Event::BomberMovedRight);
                else if (dx < 0)
                    player->triggerEvent(Event::BomberMovedLeft);
                else if (dy > 0)
                    player->triggerEvent(Event::BomberMovedDown);
                else if (dy < 0)
                    player->triggerEvent(Event::BomberMovedUp);
            }
        }
    }
}

void PlayState::update(const float deltaTime, IWorldView& renderer) {
    if (isGameOver()) {
        return;
    }

    renderer.update(deltaTime);
    if (const auto player = world->getPlayer()) {
        player->update(deltaTime);
    }
    for (auto& entity : world->getEntities()) {
        if (entity->getEntityType() == AIBomber_E) {
            static_cast<AIBomber*>(entity.get())->update(deltaTime, *world);
        } else {
            entity->update(deltaTime);
        }
    }

    world->checkExplosionCollision();
    world->checkPowerUpsCollection();
    world->removeDestroyedEntities();
    world->processNewEntities();
}

void PlayState::render(IWorldView& renderer) {
    renderer.render(*world);

    if (isGameOver()) {
        if (playerWon) {
            renderer.renderCenteredText("YOU   WIN!", 300.0f);
        } else {
            renderer.renderCenteredText("YOU   LOSE!", 300.0f);
        }
    }
}

bool PlayState::isGameOver() {
    int aliveBombers = 0;
    const auto player = world->getPlayer();
    if (player && !player->isDestroyed()) {
        aliveBombers++;
    }
    for (const auto& entity : world->getEntities()) {
        if ((entity->getEntityType() == AIBomber_E || entity->getEntityType() == KnockedOutBomber_E) && !entity->isDestroyed()) {
            aliveBombers++;
        }
    }

    if (aliveBombers <= 1) {
        playerWon = (player && !player->isDestroyed());
        return true;
    }

    return false;
}

PlayState::~PlayState() = default;
