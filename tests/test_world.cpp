#include "logic/World.h"
#include "logic/AbstractFactory.h"
#include "logic/Player.h"
#include "logic/Enemy.h"
#include "logic/Bomb.h"
#include "logic/Wall.h"
#include "logic/PowerUp.h"
#include "logic/Explosion.h"
#include <iostream>
#include <memory>

/**
 * @brief Simple mock factory for testing logic without the representation layer.
 */
class MockFactory : public logic::AbstractFactory {
public:
    std::shared_ptr<logic::Player> createPlayer(float x, float y) override {
        return std::make_shared<logic::Player>(x, y);
    }
    std::shared_ptr<logic::Enemy> createEnemy(float x, float y, int type) override {
        return std::make_shared<logic::Enemy>(x, y, type);
    }
    std::shared_ptr<logic::Bomb> createBomb(float x, float y, int range) override {
        return std::make_shared<logic::Bomb>(x, y, range);
    }
    std::shared_ptr<logic::Wall> createWall(float x, float y, bool destructible) override {
        return std::make_shared<logic::Wall>(x, y, destructible);
    }
    std::shared_ptr<logic::PowerUp> createPowerUp(float x, float y, int type) override {
        return std::make_shared<logic::PowerUp>(x, y, static_cast<logic::PowerUpType>(type));
    }
    std::shared_ptr<logic::Explosion> createExplosion(float x, float y) override {
        return std::make_shared<logic::Explosion>(x, y);
    }
};

int main() {
    std::cout << "--- Bomberman Logic Test ---" << std::endl;
    
    auto factory = std::make_shared<MockFactory>();
    logic::World world(factory);
    
    std::cout << "Initializing arena..." << std::endl;
    world.initArena();
    
    std::cout << "Running world update..." << std::endl;
    world.update();
    
    std::cout << "Current entities: " << world.getEntities().size() << std::endl;
    
    std::cout << "Logic test completed successfully!" << std::endl;
    
    return 0;
}
