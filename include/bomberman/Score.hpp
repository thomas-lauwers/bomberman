#pragma once

#include "bomberman/Observer.hpp"

#include <string>
#include <vector>

namespace bomberman {

class Score final : public IObserver {
  public:
    explicit Score(std::string highscoresPath = "highscores.txt");

    void onEvent(const GameEvent& event) override;

    void updateAliveTime(double deltaTime);
    [[nodiscard]] int current() const noexcept { return currentScore_; }

    void finishRun();
    [[nodiscard]] const std::vector<int>& highscores() const noexcept { return highscores_; }

  private:
    void loadHighscores();
    void persistHighscores() const;

    std::string highscoresPath_;
    int currentScore_{0};
    std::vector<int> highscores_{};
};

} // namespace bomberman
