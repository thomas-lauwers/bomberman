#include "bomberman/Game.hpp"

#include "bomberman/Stopwatch.hpp"

namespace bomberman {

Game::Game() : score_(std::make_shared<Score>()) { world_.attach(score_); }

void Game::update() {
    auto& stopwatch = Stopwatch::instance();
    const auto delta = stopwatch.tick();
    score_->updateAliveTime(delta);
    world_.update(delta);
}

void Game::movePlayer(const Direction direction) { world_.moveCharacter(0U, direction, Stopwatch::instance().deltaTime()); }

bool Game::placePlayerBomb() { return world_.placeBomb(0U); }

} // namespace bomberman
