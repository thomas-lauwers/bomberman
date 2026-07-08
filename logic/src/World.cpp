#include "logic/World.h"
#include "logic/Player.h"
#include "logic/Enemy.h"
#include "logic/Wall.h"
#include "logic/Bomb.h"
#include "logic/PowerUp.h"
#include "logic/Explosion.h"
#include "logic/Random.h"
#include "logic/Stopwatch.h"
#include <algorithm>

namespace logic {

World::World(std::shared_ptr<AbstractFactory> factory) : factory(factory) {}

World::~World() = default;

void World::update() {
    Stopwatch::getInstance().tick();
    for (size_t i = 0; i < entities.size(); ++i) {
        entities[i]->update();
        if (entities[i]->getType() == EntityType::Enemy && entities[i]->isAlive()) {
            static_cast<Enemy&>(*entities[i]).performAI(*this);
        }
    }
    spawnExplosions();
    handleCollisions();
    removeDestroyedEntities();
}

void World::spawnExplosions() {
    const int GRID_WIDTH = 15;
    const int GRID_HEIGHT = 13;
    const float CELL_W = 2.0f / GRID_WIDTH;
    const float CELL_H = 2.0f / GRID_HEIGHT;

    std::vector<std::shared_ptr<Entity>> newExplosions;

    for (auto& entity : entities) {
        if (entity->getType() == EntityType::Bomb) {
            Bomb& bomb = static_cast<Bomb&>(*entity);
            if (bomb.hasExploded() && !bomb.wereExplosionsSpawned()) {
                bomb.setExplosionsSpawned();
                
                newExplosions.push_back(factory->createExplosion(bomb.getX(), bomb.getY()));
                
                int range = bomb.getRange();
                int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
                
                for (auto& dir : dirs) {
                    for (int step = 1; step <= range; ++step) {
                        float ex = bomb.getX() + dir[0] * step * CELL_W;
                        float ey = bomb.getY() - dir[1] * step * CELL_H;
                        
                        bool blocked = false;
                        bool hitDestructible = false;
                        for (auto& other : entities) {
                            if (std::abs(other->getX() - ex) < 0.01f && std::abs(other->getY() - ey) < 0.01f) {
                                if (other->getType() == EntityType::Wall) {
                                    Wall& wall = static_cast<Wall&>(*other);
                                    if (wall.isDestructible()) {
                                        hitDestructible = true;
                                    } else {
                                        blocked = true;
                                    }
                                }
                                break;
                            }
                        }
                        
                        if (blocked) break;
                        newExplosions.push_back(factory->createExplosion(ex, ey));
                        if (hitDestructible) break;
                    }
                }
            }
        }
    }
    
    for (auto& explosion : newExplosions) {
        addEntity(std::move(explosion));
    }
}

void World::initArena() {
    const int GRID_WIDTH = 15;
    const int GRID_HEIGHT = 13;
    const float CELL_W = 2.0f / GRID_WIDTH;
    const float CELL_H = 2.0f / GRID_HEIGHT;

    for (int r = 0; r < GRID_HEIGHT; ++r) {
        for (int c = 0; c < GRID_WIDTH; ++c) {
            float x = -1.0f + (c + 0.5f) * CELL_W;
            float y = 1.0f - (r + 0.5f) * CELL_H;

            // Indestructible walls
            if (r % 2 == 1 && c % 2 == 1) {
                entities.push_back(factory->createWall(x, y, false));
            }
            // Border walls
            else if (r == 0 || r == GRID_HEIGHT - 1 || c == 0 || c == GRID_WIDTH - 1) {
                entities.push_back(factory->createWall(x, y, false));
            }
            // Destructible blocks and empty spaces
            else {
                // Keep corners clear for players
                bool corner = (r <= 2 && c <= 2) || (r <= 2 && c >= GRID_WIDTH - 3) ||
                             (r >= GRID_HEIGHT - 3 && c <= 2) || (r >= GRID_HEIGHT - 3 && c >= GRID_WIDTH - 3);
                
                if (!corner) {
                    if (Random::getInstance().getRandomFloat(0.0f, 1.0f) < 0.8f) {
                        entities.push_back(factory->createWall(x, y, true));
                    }
                }
            }
        }
    }

    // Players and Enemies
    entities.push_back(factory->createPlayer(-1.0f + 1.5f * CELL_W, 1.0f - 1.5f * CELL_H));
    entities.push_back(factory->createEnemy(1.0f - 1.5f * CELL_W, 1.0f - 1.5f * CELL_H, 0));
    entities.push_back(factory->createEnemy(-1.0f + 1.5f * CELL_W, -1.0f + 1.5f * CELL_H, 1));
    entities.push_back(factory->createEnemy(1.0f - 1.5f * CELL_W, -1.0f + 1.5f * CELL_H, 2));
}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(std::move(entity));
}

const std::vector<std::shared_ptr<Entity>>& World::getEntities() const {
    return entities;
}

void World::movePlayer(float dx, float dy) {
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::Player && entity->isAlive()) {
            Player& player = static_cast<Player&>(*entity);
            float oldX = player.getX();
            float oldY = player.getY();
            
            player.move(dx, 0);
            if (checkSolidCollision(player)) {
                player.setPosition(oldX, oldY);
            }
            
            oldX = player.getX();
            oldY = player.getY();
            player.move(0, dy);
            if (checkSolidCollision(player)) {
                player.setPosition(oldX, oldY);
            }
            break;
        }
    }
}

void World::moveEnemy(Enemy& enemy, float dx, float dy) {
    float oldX = enemy.getX();
    float oldY = enemy.getY();
    float speed = 0.02f;
    
    enemy.setPosition(oldX + dx * speed, oldY);
    if (checkSolidCollision(enemy)) {
        enemy.setPosition(oldX, oldY);
    }
    
    oldX = enemy.getX();
    oldY = enemy.getY();
    enemy.setPosition(oldX, oldY + dy * speed);
    if (checkSolidCollision(enemy)) {
        enemy.setPosition(oldX, oldY);
    }
}

void World::playerPlaceBomb() {
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::Player && entity->isAlive()) {
            Player& player = static_cast<Player&>(*entity);
            if (player.canPlaceBomb()) {
                // Align bomb to grid
                const int GRID_WIDTH = 15;
                const int GRID_HEIGHT = 13;
                const float CELL_W = 2.0f / GRID_WIDTH;
                const float CELL_H = 2.0f / GRID_HEIGHT;
                
                int c = static_cast<int>((player.getX() + 1.0f) / CELL_W);
                int r = static_cast<int>((1.0f - player.getY()) / CELL_H);
                
                float bx = -1.0f + (c + 0.5f) * CELL_W;
                float by = 1.0f - (r + 0.5f) * CELL_H;
                
                // Check if a bomb already exists at this position
                bool alreadyBomb = false;
                for (auto& other : entities) {
                    if (other->getType() == EntityType::Bomb && 
                        std::abs(other->getX() - bx) < 0.01f && 
                        std::abs(other->getY() - by) < 0.01f) {
                        alreadyBomb = true;
                        break;
                    }
                }
                
                if (!alreadyBomb) {
                    player.placeBomb();
                    addEntity(factory->createBomb(bx, by, 1)); // TODO: use player's range
                }
            }
            break;
        }
    }
}

void World::handleCollisions() {
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            auto& e1 = entities[i];
            auto& e2 = entities[j];

            if (!e1->isAlive() || !e2->isAlive()) continue;

            float min1X, min1Y, max1X, max1Y;
            float min2X, min2Y, max2X, max2Y;
            e1->getAABB(min1X, min1Y, max1X, max1Y);
            e2->getAABB(min2X, min2Y, max2X, max2Y);

            if (max1X > min2X && min1X < max2X && max1Y > min2Y && min1Y < max2Y) {
                EntityType t1 = e1->getType();
                EntityType t2 = e2->getType();

                if (t1 == EntityType::Explosion) {
                    handleExplosionCollision(*e1, *e2);
                } else if (t2 == EntityType::Explosion) {
                    handleExplosionCollision(*e2, *e1);
                } else if (t1 == EntityType::Player && t2 == EntityType::PowerUp) {
                    handlePlayerPowerUpCollision(*e1, *e2);
                } else if (t2 == EntityType::Player && t1 == EntityType::PowerUp) {
                    handlePlayerPowerUpCollision(*e2, *e1);
                }
            }
        }
    }
}

void World::handleExplosionCollision(Entity&, Entity& other) {
    EntityType type = other.getType();
    if (type == EntityType::Player) {
        static_cast<Player&>(other).kill();
        score.addPoints(-500);
    } else if (type == EntityType::Enemy) {
        if (other.isAlive()) {
            static_cast<Enemy&>(other).kill();
            score.addPoints(1000);
        }
    } else if (type == EntityType::Wall) {
        Wall& wall = static_cast<Wall&>(other);
        if (wall.isDestructible()) {
            wall.destroy();
            score.addPoints(10);
            if (Random::getInstance().getRandomFloat(0.0f, 1.0f) < 0.25f) {
                PowerUpType puType = static_cast<PowerUpType>(Random::getInstance().getRandomInt(0, 2));
                addEntity(factory->createPowerUp(wall.getX(), wall.getY(), static_cast<int>(puType)));
            }
        }
    } else if (type == EntityType::Bomb) {
        static_cast<Bomb&>(other).trigger();
    } else if (type == EntityType::PowerUp) {
        static_cast<PowerUp&>(other).collect();
    }
}

void World::handlePlayerPowerUpCollision(Entity& playerEntity, Entity& powerUpEntity) {
    Player& player = static_cast<Player&>(playerEntity);
    PowerUp& powerUp = static_cast<PowerUp&>(powerUpEntity);
    
    PowerUpType puType = powerUp.getPowerUpType();
    if (puType == PowerUpType::Fire) player.increaseRange();
    else if (puType == PowerUpType::ExtraBomb) player.increaseBombCapacity();
    else if (puType == PowerUpType::Skates) player.increaseSpeed();
    
    score.addPoints(50);
    powerUp.collect();
}

bool World::checkSolidCollision(const Entity& e) {
    float min1X, min1Y, max1X, max1Y;
    e.getAABB(min1X, min1Y, max1X, max1Y);

    for (auto& other : entities) {
        if (other.get() == &e || !other->isAlive() || !other->isSolid()) continue;

        float min2X, min2Y, max2X, max2Y;
        other->getAABB(min2X, min2Y, max2X, max2Y);

        if (max1X > min2X && min1X < max2X && max1Y > min2Y && min1Y < max2Y) {
            return true;
        }
    }
    return false;
}

void World::removeDestroyedEntities() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](const std::shared_ptr<Entity>& e) {
            return !e->isAlive();
        }), entities.end());
}

} // namespace logic
