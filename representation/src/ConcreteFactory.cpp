#include "representation/ConcreteFactory.h"
#include "logic/Player.h"
#include "logic/Enemy.h"
#include "logic/Bomb.h"
#include "logic/Wall.h"
#include "logic/PowerUp.h"
#include "logic/Explosion.h"
#include <algorithm>

namespace rep {

ConcreteFactory::ConcreteFactory() = default;

std::shared_ptr<logic::Player> ConcreteFactory::createPlayer(float x, float y) {
    auto player = std::make_shared<logic::Player>(x, y);
    auto view = std::make_shared<PlayerView>(player);
    player->attach(view.get());
    views.push_back(view);
    return player;
}

std::shared_ptr<logic::Enemy> ConcreteFactory::createEnemy(float x, float y, int type) {
    auto enemy = std::make_shared<logic::Enemy>(x, y, type);
    auto view = std::make_shared<EnemyView>(enemy);
    enemy->attach(view.get());
    views.push_back(view);
    return enemy;
}

std::shared_ptr<logic::Bomb> ConcreteFactory::createBomb(float x, float y, int range) {
    auto bomb = std::make_shared<logic::Bomb>(x, y, range);
    auto view = std::make_shared<BombView>(bomb);
    bomb->attach(view.get());
    views.push_back(view);
    return bomb;
}

std::shared_ptr<logic::Wall> ConcreteFactory::createWall(float x, float y, bool destructible) {
    auto wall = std::make_shared<logic::Wall>(x, y, destructible);
    auto view = std::make_shared<WallView>(wall);
    wall->attach(view.get());
    views.push_back(view);
    return wall;
}

std::shared_ptr<logic::PowerUp> ConcreteFactory::createPowerUp(float x, float y, int type) {
    auto powerUp = std::make_shared<logic::PowerUp>(x, y, static_cast<logic::PowerUpType>(type));
    auto view = std::make_shared<PowerUpView>(powerUp);
    powerUp->attach(view.get());
    views.push_back(view);
    return powerUp;
}

std::shared_ptr<logic::Explosion> ConcreteFactory::createExplosion(float x, float y) {
    auto explosion = std::make_shared<logic::Explosion>(x, y);
    auto view = std::make_shared<ExplosionView>(explosion);
    explosion->attach(view.get());
    views.push_back(view);
    return explosion;
}

const std::vector<std::shared_ptr<View>>& ConcreteFactory::getViews() const {
    return views;
}

void ConcreteFactory::cleanup() {
    views.erase(std::remove_if(views.begin(), views.end(),
        [](const std::shared_ptr<View>& v) {
            return !v->isAlive();
        }), views.end());
}

} // namespace rep
