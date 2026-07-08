#pragma once

#include <cstddef>

namespace bomberman {

struct Vec2 {
    double x{0.0};
    double y{0.0};
};

enum class Direction { Up, Down, Left, Right, None };

enum class TileType { Empty, Indestructible, Destructible };

enum class PowerUpType { Fire, ExtraBomb, Skates };

enum class GameEventType {
    Tick,
    BlockDestroyed,
    PowerUpPicked,
    EnemyKilled,
    PlayerWon,
    PlayerLost
};

struct GameEvent {
    GameEventType type{GameEventType::Tick};
    std::size_t actorId{0U};
};

} // namespace bomberman
