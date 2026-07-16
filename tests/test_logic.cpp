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
    p.setCanPlaceBomb(false);
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
    world->pushBackEntity(factory->createBomb(static_cast<float>(wx), static_cast<float>(wy)));
    
    // Spawn explosion on the wall
    world->spawnExplosion(static_cast<float>(wx), static_cast<float>(wy));
    
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
    Bomb b(1.0f, 1.0f);
    EXPECT_FALSE(b.isDestroyed());
    b.explode();
    EXPECT_TRUE(b.isDestroyed());
}

TEST(WorldTest, AddEntities) {
    const auto factory = std::make_shared<TestEntityFactory>();
    auto world = std::make_shared<World>(factory);
    const size_t initialSize = world->getEntities().size();
    world->pushBackEntity(factory->createBomb(1.0f, 1.0f));
    EXPECT_EQ(world->getEntities().size(), initialSize + 1);
}

TEST(CrumblingWallTest, Destruction) {
    CrumblingWall w(1.0f, 1.0f);
    EXPECT_FALSE(w.isDestroyed());
    w.destroy();
    EXPECT_TRUE(w.isDestroyed());
}
