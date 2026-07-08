#include "TestFramework.hpp"

#include "bomberman/Camera.hpp"
#include "bomberman/Random.hpp"
#include "bomberman/Score.hpp"
#include "bomberman/World.hpp"

#include <algorithm>
#include <filesystem>

TEST(WorldSpawnsCharactersInAllCornersAndPlayerTopLeft) {
    bomberman::Random::instance().reseed(7U);
    bomberman::World world;
    const auto& characters = world.characters();
    CHECK(characters.size() == 4U);
    CHECK(characters[0].isPlayer);

    const auto& arena = world.arena();
    CHECK(arena[1][1] == bomberman::TileType::Empty);
    CHECK(arena[1][arena[0].size() - 2] == bomberman::TileType::Empty);
    CHECK(arena[arena.size() - 2][1] == bomberman::TileType::Empty);
    CHECK(arena[arena.size() - 2][arena[0].size() - 2] == bomberman::TileType::Empty);
}

TEST(BombsExplodeAndCanDestroyBreakableBlocks) {
    bomberman::Random::instance().reseed(11U);
    bomberman::World world;

    bool breakableFound = false;
    for (const auto& row : world.arena()) {
        if (std::find(row.begin(), row.end(), bomberman::TileType::Destructible) != row.end()) {
            breakableFound = true;
            break;
        }
    }
    CHECK(breakableFound);

    CHECK(world.placeBomb(0U));
    world.update(2.1);

    bool anyoneDead = false;
    for (const auto& character : world.characters()) {
        if (!character.alive) {
            anyoneDead = true;
        }
    }
    CHECK(anyoneDead);
}

TEST(CameraConvertsNormalizedCoordinatesToPixels) {
    bomberman::Camera camera(801U, 601U);
    const auto [centerX, centerY] = camera.toPixel(bomberman::Vec2{});
    CHECK(centerX == 400);
    CHECK(centerY == 300);

    const auto normalized = camera.toNormalized(centerX, centerY);
    CHECK(normalized.x > -0.01 && normalized.x < 0.01);
    CHECK(normalized.y > -0.01 && normalized.y < 0.01);
}

TEST(ScoreTracksEventsAndPersistsTopFive) {
    const auto path = std::filesystem::temp_directory_path() / "bomberman-score-test.txt";
    {
        bomberman::Score score(path.string());
        score.updateAliveTime(3.0);
        score.onEvent(bomberman::GameEvent{.type = bomberman::GameEventType::BlockDestroyed});
        score.onEvent(bomberman::GameEvent{.type = bomberman::GameEventType::PowerUpPicked});
        score.onEvent(bomberman::GameEvent{.type = bomberman::GameEventType::EnemyKilled});
        score.onEvent(bomberman::GameEvent{.type = bomberman::GameEventType::PlayerWon});
        score.finishRun();
        CHECK(score.current() > 0);
    }
    {
        bomberman::Score score(path.string());
        CHECK(!score.highscores().empty());
        CHECK(score.highscores().size() <= 5U);
    }

    std::filesystem::remove(path);
}
