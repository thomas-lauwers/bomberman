#pragma once

#include "bomberman/Score.hpp"
#include "bomberman/World.hpp"

#include <memory>

namespace bomberman {

class Game {
  public:
    Game();

    void update();
    void movePlayer(Direction direction);
    bool placePlayerBomb();

    [[nodiscard]] const World& world() const noexcept { return world_; }
    [[nodiscard]] const Score& score() const noexcept { return *score_; }

  private:
    World world_{};
    std::shared_ptr<Score> score_{};
};

} // namespace bomberman
