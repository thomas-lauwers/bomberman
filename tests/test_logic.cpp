#include <gtest/gtest.h>
#include "../include/logic/Rect.h"
#include "../include/logic/Tile.h"
#include "../include/logic/World.h"
#include "../include/logic/factory/Bomb.h"
#include "../include/logic/factory/DestructibleWall.h"
#include "../include/logic/factory/CrumblingWall.h"
#include "../include/logic/factory/Player.h"
#include "../include/utils/Position.h"
#include "TestEntityFactory.h"

TEST(RectTest, Intersects) {
    // Overlapping rectangles
    const Rect r1{0, 0, 10, 10};
    const Rect r2{5, 5, 10, 10};
    EXPECT_TRUE(r1.intersects(r2));
    EXPECT_TRUE(r2.intersects(r1));

    // Non-overlapping rectangles
    const Rect r3{20, 20, 10, 10};
    EXPECT_FALSE(r1.intersects(r3));
    EXPECT_FALSE(r3.intersects(r1));

    // Adjacent but not overlapping
    const Rect r4{10, 0, 10, 10};
    EXPECT_FALSE(r1.intersects(r4));

    // Completely inside
    const Rect r5{2, 2, 2, 2};
    EXPECT_TRUE(r1.intersects(r5));
}

TEST(TileTest, Type) {
    Tile t1{TileType::E};
    EXPECT_EQ(t1.getType(), TileType::E);
    
    t1.setType(TileType::W);
    EXPECT_EQ(t1.getType(), TileType::W);

    const Tile t2{TileType::W};
    EXPECT_EQ(t2.getType(), TileType::W);
}

TEST(PlayerTest, CanPlaceBomb) {
    Player p;
    EXPECT_TRUE(p.canPlaceBomb());
    p.placeBomb();
    EXPECT_FALSE(p.canPlaceBomb());
}

TEST(WorldTest, Collision) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    
    // Player at (1.2, 1.0)
    const auto player = std::make_shared<Player>();
    player->setPosition(1.2f, 1.0f);
    world->setPlayer(player);
    
    // Wall at (2.0, 1.0)
    world->pushBackEntity(factory->createDestructibleWall(2.0f, 1.0f));
    
    // Collision should be detected
    EXPECT_TRUE(world->isColliding(player->getCollisionRect(), nullptr, player->getCollisionRect()));
}

TEST(WorldTest, ExplosionDestroysWall) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    
    // Manually place a destructible wall
    const int wx = 1;
    const int wy = 2;
    world->pushBackEntity(factory->createDestructibleWall(static_cast<float>(wx), static_cast<float>(wy)));
    
    EXPECT_TRUE(world->isDestructibleWallAt(wx, wy));
    
    // Place a bomb and trigger explosion
    world->pushBackEntity(factory->createBomb(static_cast<float>(wx), static_cast<float>(wy), 1));
    
    // Spawn explosion on the wall
    world->spawnExplosion(static_cast<float>(wx), static_cast<float>(wy), 1);
    
    // Check if the entity is destroyed
    world->removeDestroyedEntities();
    
    EXPECT_FALSE(world->isDestructibleWallAt(wx, wy));
}

TEST(PlayerTest, Position) {
    Player p;
    p.setPosition(5.5f, 6.5f);
    Position pos = p.getPosition();
    EXPECT_FLOAT_EQ(pos.x, 5.5f);
    EXPECT_FLOAT_EQ(pos.y, 6.5f);
}

TEST(EntityTest, DestroyedState) {
    DestructibleWall w(1.0f, 1.0f);
    EXPECT_FALSE(w.isDestroyed());
    w.destroy();
    EXPECT_TRUE(w.isDestroyed());
}

TEST(BombTest, Explode) {
    Bomb b(1.0f, 1.0f, 1);
    EXPECT_FALSE(b.isDestroyed());
    b.explode();
    EXPECT_TRUE(b.isDestroyed());
}

TEST(WorldTest, AddEntities) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    const size_t initialSize = world->getEntities().size();
    world->pushBackEntity(factory->createBomb(1.0f, 1.0f, 1));
    EXPECT_EQ(world->getEntities().size(), initialSize + 1);
}

TEST(CrumblingWallTest, Destruction) {
    CrumblingWall w(1.0f, 1.0f);
    EXPECT_FALSE(w.isDestroyed());
    w.destroy();
    EXPECT_TRUE(w.isDestroyed());
}

TEST(BombTest, BlastRadius) {
    Bomb b(1.0f, 1.0f, 5);
    EXPECT_EQ(b.getBlastRadius(), 5);
}

TEST(PlayerTest, InitialPosition) {
    Player p;
    Position pos = p.getPosition();
    EXPECT_FLOAT_EQ(pos.x, 1.0f);
    EXPECT_FLOAT_EQ(pos.y, 1.0f);
}

TEST(WorldTest, RemoveEntity) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    auto wall = factory->createDestructibleWall(1.0f, 1.0f);
    auto* raw_wall = wall.get();
    world->pushBackEntity(std::move(wall));
    size_t sizeAfterAdd = world->getEntities().size();
    raw_wall->destroy();
    world->removeDestroyedEntities();
    EXPECT_EQ(world->getEntities().size(), sizeAfterAdd - 1);
}

TEST(WorldTest, ExplosionBlocksMovement) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    
    // Bomber at (1.0, 1.0)
    auto bomber = factory->createAIBomber(1.0f, 1.0f, BomberType::Variant1);
    
    // Explosion at (2.0, 1.0)
    world->pushBackEntity(factory->createExplosion(2.0f, 1.0f, ExplosionType::Center));
    
    // Collision should be detected (true = collision)
    // Bomber's collision rect should now intersect with explosion's
    // (We need to make sure the bomber's collision rect is positioned at a place where it intersects)
    // If bomber is at (1.0, 1.0), and explosion is at (2.0, 1.0), do they intersect?
    // Bomber at (1.0, 1.0) -> rect at [1.2, 1.2, 0.6, 0.6]
    // Explosion at (2.0, 1.0) -> rect at [2.0, 1.0, 0.8, 0.8]
    // No intersection. 
    // Let's place the explosion AT (1.0, 1.0).
    
    world->pushBackEntity(factory->createExplosion(1.0f, 1.0f, ExplosionType::Center));
    // Bomber at 1.0, 1.0 -> Rect [1.2, 1.2, 0.6, 0.6]
    // Explosion at 1.0, 1.0 -> Rect [1.0, 1.0, 0.8, 0.8]
    // Intersection:
    // Bomber X: 1.2 to 1.8
    // Explosion X: 1.0 to 1.8
    // Yes! Intersection [1.2, 1.8]!
    
    EXPECT_TRUE(world->isColliding(bomber->getCollisionRect(), nullptr, bomber->getCollisionRect()));
}

TEST(EntityTest, NewEntityNotDestroyed) {
    DestructibleWall w(2.0f, 2.0f);
    EXPECT_FALSE(w.isDestroyed());
}

TEST(AIBomberTest, IsInDanger) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    
    // Place a bomb at (2, 2) with blast radius 3
    world->pushBackEntity(factory->createBomb(2.0f, 2.0f, 3));
    
    // Bomber at (2, 3)
    auto aiBomber = factory->createAIBomber(2.0f, 3.0f, BomberType::Variant1);
    
    // (2, 3) should be in danger
    EXPECT_TRUE(aiBomber->isInDanger(*world));
}

TEST(AIBomberTest, IsNotInDangerAfterBombDestroyed) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    
    // Place a bomb at (2, 2) with blast radius 3
    auto bomb = factory->createBomb(2.0f, 2.0f, 3);
    auto* raw_bomb = bomb.get();
    world->pushBackEntity(std::move(bomb));
    
    // Bomber at (2, 3)
    auto aiBomber = factory->createAIBomber(2.0f, 3.0f, BomberType::Variant1);
    
    // (2, 3) should be in danger
    EXPECT_TRUE(aiBomber->isInDanger(*world));
    
    // Destroy the bomb
    raw_bomb->destroy();
    
    // Bomber should NOT be in danger now
    EXPECT_FALSE(aiBomber->isInDanger(*world));
}

