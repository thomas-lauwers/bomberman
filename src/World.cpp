#include "bomberman/World.hpp"

#include "bomberman/Random.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>

namespace bomberman {

namespace {
constexpr double kBombFuseSeconds = 2.0;
constexpr double kPowerUpDropChance = 0.25;
} // namespace

World::World(const std::size_t width, const std::size_t height) : width_(width), height_(height) { initialize(); }

void World::initialize() {
    arena_.assign(height_, std::vector<TileType>(width_, TileType::Empty));
    bombs_.clear();
    powerUps_.clear();
    characters_.clear();

    auto& random = Random::instance();
    for (int y = 0; y < height(); ++y) {
        for (int x = 0; x < width(); ++x) {
            const bool border = x == 0 || y == 0 || x == width() - 1 || y == height() - 1;
            const bool pillar = (x % 2 == 0) && (y % 2 == 0);
            if (border || pillar) {
                arena_[y][x] = TileType::Indestructible;
            } else {
                arena_[y][x] = random.chance(0.2) ? TileType::Empty : TileType::Destructible;
            }
        }
    }

    const std::vector<std::pair<int, int>> spawnTiles{{1, 1}, {width() - 2, 1}, {1, height() - 2}, {width() - 2, height() - 2}};
    for (const auto [x, y] : spawnTiles) {
        arena_[y][x] = TileType::Empty;
        if (x + 1 < width()) {
            arena_[y][x + 1] = TileType::Empty;
        }
        if (y + 1 < height()) {
            arena_[y + 1][x] = TileType::Empty;
        }
    }

    characters_.push_back(Character{.id = 0U, .isPlayer = true, .alive = true, .position = toNormalized(1, 1)});
    characters_.push_back(Character{.id = 1U, .isPlayer = false, .alive = true, .position = toNormalized(width() - 2, 1)});
    characters_.push_back(Character{.id = 2U, .isPlayer = false, .alive = true, .position = toNormalized(1, height() - 2)});
    characters_.push_back(Character{.id = 3U, .isPlayer = false, .alive = true, .position = toNormalized(width() - 2, height() - 2)});
}

void World::setFactory(std::shared_ptr<AbstractFactory> factory) {
    factory_ = std::move(factory);
    if (factory_) {
        attach(factory_->createWorldView());
    }
}

void World::update(const double deltaTime) {
    updateBots(deltaTime);

    for (std::size_t i = 0; i < bombs_.size();) {
        bombs_[i].timer -= deltaTime;
        if (bombs_[i].timer <= 0.0) {
            explodeBomb(i);
        } else {
            ++i;
        }
    }

    for (auto& character : characters_) {
        if (!character.alive) {
            continue;
        }
        collectPowerUp(character);
    }
}

void World::moveCharacter(const std::size_t characterId, const Direction direction, const double deltaTime) {
    if (characterId >= characters_.size() || direction == Direction::None || !characters_[characterId].alive) {
        return;
    }

    auto& character = characters_[characterId];
    Vec2 next = character.position;

    const double delta = character.speed * deltaTime;
    switch (direction) {
    case Direction::Up:
        next.y -= delta;
        break;
    case Direction::Down:
        next.y += delta;
        break;
    case Direction::Left:
        next.x -= delta;
        break;
    case Direction::Right:
        next.x += delta;
        break;
    case Direction::None:
        return;
    }

    const auto [tileX, tileY] = toTile(next);
    if (canOccupyTile(tileX, tileY)) {
        character.position = next;
    }
}

bool World::placeBomb(const std::size_t characterId) {
    if (characterId >= characters_.size()) {
        return false;
    }

    auto& character = characters_[characterId];
    if (!character.alive || character.activeBombs >= character.maxBombs) {
        return false;
    }

    const auto [tileX, tileY] = toTile(character.position);
    const auto duplicate = std::find_if(bombs_.begin(), bombs_.end(), [tileX, tileY](const Bomb& bomb) {
        return bomb.tileX == tileX && bomb.tileY == tileY;
    });
    if (duplicate != bombs_.end()) {
        return false;
    }

    bombs_.push_back(Bomb{.ownerId = characterId, .tileX = tileX, .tileY = tileY, .radius = character.blastRadius, .timer = kBombFuseSeconds});
    ++character.activeBombs;
    return true;
}

bool World::hasBreakableTiles() const {
    for (const auto& row : arena_) {
        if (std::any_of(row.begin(), row.end(), [](TileType tile) { return tile == TileType::Destructible; })) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> World::toTile(const Vec2& position) const {
    const auto normalizedToTile = [](const double value, const int max) {
        const double translated = ((std::clamp(value, -1.0, 1.0) + 1.0) / 2.0) * static_cast<double>(max);
        return static_cast<int>(std::round(translated));
    };
    return {std::clamp(normalizedToTile(position.x, width() - 1), 0, width() - 1),
            std::clamp(normalizedToTile(position.y, height() - 1), 0, height() - 1)};
}

Vec2 World::toNormalized(const int tileX, const int tileY) const {
    return {
        (2.0 * static_cast<double>(tileX) / static_cast<double>(width() - 1)) - 1.0,
        (2.0 * static_cast<double>(tileY) / static_cast<double>(height() - 1)) - 1.0,
    };
}

bool World::canOccupyTile(const int tileX, const int tileY) const {
    if (tileX < 0 || tileY < 0 || tileX >= width() || tileY >= height()) {
        return false;
    }

    if (arena_[tileY][tileX] != TileType::Empty) {
        return false;
    }

    return std::none_of(bombs_.begin(), bombs_.end(), [tileX, tileY](const Bomb& bomb) {
        return bomb.tileX == tileX && bomb.tileY == tileY;
    });
}

void World::explodeBomb(const std::size_t bombIndex) {
    Bomb bomb = bombs_[bombIndex];

    auto owner = std::find_if(characters_.begin(), characters_.end(), [&bomb](const Character& character) {
        return character.id == bomb.ownerId;
    });
    if (owner != characters_.end() && owner->activeBombs > 0) {
        --owner->activeBombs;
    }

    bool stop = false;
    processExplosionTile(bomb.ownerId, bomb.tileX, bomb.tileY, stop);

    for (const auto [dx, dy] : std::vector<std::pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
        for (int step = 1; step <= bomb.radius; ++step) {
            bool directionStop = false;
            processExplosionTile(bomb.ownerId, bomb.tileX + dx * step, bomb.tileY + dy * step, directionStop);
            if (directionStop) {
                break;
            }
        }
    }

    bombs_.erase(bombs_.begin() + static_cast<std::ptrdiff_t>(bombIndex));
}

void World::processExplosionTile(const std::size_t ownerId, const int tileX, const int tileY, bool& stopDirection) {
    if (tileX < 0 || tileY < 0 || tileX >= width() || tileY >= height()) {
        stopDirection = true;
        return;
    }

    if (arena_[tileY][tileX] == TileType::Indestructible) {
        stopDirection = true;
        return;
    }

    if (arena_[tileY][tileX] == TileType::Destructible) {
        arena_[tileY][tileX] = TileType::Empty;
        notify(GameEvent{.type = GameEventType::BlockDestroyed, .actorId = ownerId});

        if (Random::instance().chance(kPowerUpDropChance)) {
            const auto pick = Random::instance().rangeInt(0, 2);
            powerUps_.push_back(PowerUp{.tileX = tileX,
                                        .tileY = tileY,
                                        .type = static_cast<PowerUpType>(pick)});
        }

        stopDirection = true;
    }

    for (auto& bomb : bombs_) {
        if (bomb.tileX == tileX && bomb.tileY == tileY) {
            bomb.timer = 0.0;
        }
    }

    for (auto& character : characters_) {
        if (!character.alive) {
            continue;
        }
        const auto [x, y] = toTile(character.position);
        if (x == tileX && y == tileY) {
            character.alive = false;
            if (!character.isPlayer) {
                notify(GameEvent{.type = GameEventType::EnemyKilled, .actorId = ownerId});
            } else {
                notify(GameEvent{.type = GameEventType::PlayerLost, .actorId = ownerId});
            }
        }
    }

    powerUps_.erase(std::remove_if(powerUps_.begin(),
                                   powerUps_.end(),
                                   [tileX, tileY](const PowerUp& powerUp) {
                                       return powerUp.tileX == tileX && powerUp.tileY == tileY;
                                   }),
                    powerUps_.end());
}

void World::collectPowerUp(Character& character) {
    const auto [tileX, tileY] = toTile(character.position);
    const auto powerUpIterator = std::find_if(powerUps_.begin(), powerUps_.end(), [tileX, tileY](const PowerUp& powerUp) {
        return powerUp.tileX == tileX && powerUp.tileY == tileY;
    });

    if (powerUpIterator == powerUps_.end()) {
        return;
    }

    switch (powerUpIterator->type) {
    case PowerUpType::Fire:
        ++character.blastRadius;
        break;
    case PowerUpType::ExtraBomb:
        ++character.maxBombs;
        break;
    case PowerUpType::Skates:
        character.speed += 0.15;
        break;
    }

    notify(GameEvent{.type = GameEventType::PowerUpPicked, .actorId = character.id});
    powerUps_.erase(powerUpIterator);
}

void World::updateBots(const double deltaTime) {
    for (auto& bot : characters_) {
        if (bot.isPlayer || !bot.alive) {
            continue;
        }

        const auto [botX, botY] = toTile(bot.position);

        if (const auto dangerDirection = safestDirection(bot); dangerDirection.has_value()) {
            moveCharacter(bot.id, *dangerDirection, deltaTime);
            continue;
        }

        auto nearestPowerUpDistance = std::numeric_limits<int>::max();
        std::optional<PowerUp> nearestPowerUp;
        for (const auto& powerUp : powerUps_) {
            const int distance = std::abs(powerUp.tileX - botX) + std::abs(powerUp.tileY - botY);
            if (distance < nearestPowerUpDistance) {
                nearestPowerUpDistance = distance;
                nearestPowerUp = powerUp;
            }
        }

        if (nearestPowerUp.has_value() && nearestPowerUpDistance <= 4) {
            moveTowards(bot, nearestPowerUp->tileX, nearestPowerUp->tileY, deltaTime);
            continue;
        }

        bool placedBomb = false;
        for (const auto [dx, dy] : std::vector<std::pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
            const int nx = botX + dx;
            const int ny = botY + dy;
            if (nx < 0 || ny < 0 || nx >= width() || ny >= height()) {
                continue;
            }
            if (arena_[ny][nx] == TileType::Destructible) {
                placedBomb = placeBomb(bot.id);
                break;
            }
        }

        if (!placedBomb) {
            std::vector<Character> livingTargets;
            for (const auto& character : characters_) {
                if (character.alive && character.id != bot.id) {
                    livingTargets.push_back(character);
                }
            }
            if (!livingTargets.empty()) {
                const auto target = std::min_element(livingTargets.begin(),
                                                     livingTargets.end(),
                                                     [this, botX, botY](const Character& lhs, const Character& rhs) {
                                                         const auto [lx, ly] = toTile(lhs.position);
                                                         const auto [rx, ry] = toTile(rhs.position);
                                                         const int left = std::abs(lx - botX) + std::abs(ly - botY);
                                                         const int right = std::abs(rx - botX) + std::abs(ry - botY);
                                                         return left < right;
                                                     });
                const auto [targetX, targetY] = toTile(target->position);
                if (std::abs(targetX - botX) + std::abs(targetY - botY) <= 1) {
                    placeBomb(bot.id);
                } else {
                    moveTowards(bot, targetX, targetY, deltaTime);
                }
            }
        }
    }

    const auto aliveBots = std::count_if(characters_.begin(), characters_.end(), [](const Character& character) {
        return character.alive && !character.isPlayer;
    });
    const auto playerAlive = std::find_if(characters_.begin(), characters_.end(), [](const Character& character) {
        return character.isPlayer && character.alive;
    });

    if (aliveBots == 0 && playerAlive != characters_.end()) {
        notify(GameEvent{.type = GameEventType::PlayerWon, .actorId = playerAlive->id});
    }
}

void World::moveTowards(Character& character, const int targetX, const int targetY, const double deltaTime) {
    const auto [tileX, tileY] = toTile(character.position);
    const int dx = targetX - tileX;
    const int dy = targetY - tileY;

    if (std::abs(dx) > std::abs(dy)) {
        moveCharacter(character.id, dx > 0 ? Direction::Right : Direction::Left, deltaTime);
    } else if (dy != 0) {
        moveCharacter(character.id, dy > 0 ? Direction::Down : Direction::Up, deltaTime);
    } else if (dx != 0) {
        moveCharacter(character.id, dx > 0 ? Direction::Right : Direction::Left, deltaTime);
    }
}

std::optional<Direction> World::safestDirection(const Character& character) const {
    const auto [tileX, tileY] = toTile(character.position);
    if (!isInDanger(tileX, tileY)) {
        return std::nullopt;
    }

    for (const auto [direction, dx, dy] : std::vector<std::tuple<Direction, int, int>>{{Direction::Up, 0, -1},
                                                                                         {Direction::Down, 0, 1},
                                                                                         {Direction::Left, -1, 0},
                                                                                         {Direction::Right, 1, 0}}) {
        const int nextX = tileX + dx;
        const int nextY = tileY + dy;
        if (canOccupyTile(nextX, nextY) && !isInDanger(nextX, nextY)) {
            return direction;
        }
    }

    return std::nullopt;
}

bool World::isInDanger(const int tileX, const int tileY) const {
    for (const auto& bomb : bombs_) {
        if (bomb.timer > 1.0) {
            continue;
        }

        if (bomb.tileX == tileX) {
            const int distance = std::abs(bomb.tileY - tileY);
            if (distance <= bomb.radius) {
                return true;
            }
        }
        if (bomb.tileY == tileY) {
            const int distance = std::abs(bomb.tileX - tileX);
            if (distance <= bomb.radius) {
                return true;
            }
        }
    }

    return false;
}

} // namespace bomberman
