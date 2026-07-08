#pragma once

#include "bomberman/Factory.hpp"
#include "bomberman/Observer.hpp"
#include "bomberman/Types.hpp"

#include <cstddef>
#include <optional>
#include <unordered_map>
#include <vector>

namespace bomberman {

struct Character {
    std::size_t id{0U};
    bool isPlayer{false};
    bool alive{true};
    Vec2 position{};
    double speed{0.75};
    int blastRadius{1};
    int maxBombs{1};
    int activeBombs{0};
};

struct Bomb {
    std::size_t ownerId{0U};
    int tileX{0};
    int tileY{0};
    int radius{1};
    double timer{2.0};
};

struct PowerUp {
    int tileX{0};
    int tileY{0};
    PowerUpType type{PowerUpType::Fire};
};

class World final : public Subject {
  public:
    explicit World(std::size_t width = 13U, std::size_t height = 11U);

    void initialize();
    void setFactory(std::shared_ptr<AbstractFactory> factory);

    void update(double deltaTime);
    void moveCharacter(std::size_t characterId, Direction direction, double deltaTime);
    bool placeBomb(std::size_t characterId);

    [[nodiscard]] const std::vector<std::vector<TileType>>& arena() const noexcept { return arena_; }
    [[nodiscard]] const std::vector<Character>& characters() const noexcept { return characters_; }
    [[nodiscard]] const std::vector<PowerUp>& powerUps() const noexcept { return powerUps_; }

    [[nodiscard]] bool hasBreakableTiles() const;

  private:
    [[nodiscard]] int width() const noexcept { return static_cast<int>(width_); }
    [[nodiscard]] int height() const noexcept { return static_cast<int>(height_); }
    [[nodiscard]] std::pair<int, int> toTile(const Vec2& position) const;
    [[nodiscard]] Vec2 toNormalized(int tileX, int tileY) const;
    [[nodiscard]] bool canOccupyTile(int tileX, int tileY) const;

    void explodeBomb(std::size_t bombIndex);
    void processExplosionTile(std::size_t ownerId, int tileX, int tileY, bool& stopDirection);
    void collectPowerUp(Character& character);
    void updateBots(double deltaTime);
    void moveTowards(Character& character, int targetX, int targetY, double deltaTime);
    [[nodiscard]] std::optional<Direction> safestDirection(const Character& character) const;
    [[nodiscard]] bool isInDanger(int tileX, int tileY) const;

    std::size_t width_;
    std::size_t height_;
    std::vector<std::vector<TileType>> arena_{};
    std::vector<Character> characters_{};
    std::vector<Bomb> bombs_{};
    std::vector<PowerUp> powerUps_{};
    std::shared_ptr<AbstractFactory> factory_{};
};

} // namespace bomberman
