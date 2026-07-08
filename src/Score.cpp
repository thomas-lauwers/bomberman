#include "bomberman/Score.hpp"

#include <algorithm>
#include <fstream>

namespace bomberman {

namespace {
constexpr int kMaxHighscores = 5;
}

Score::Score(std::string highscoresPath) : highscoresPath_(std::move(highscoresPath)) { loadHighscores(); }

void Score::onEvent(const GameEvent& event) {
    switch (event.type) {
    case GameEventType::Tick:
        break;
    case GameEventType::BlockDestroyed:
        currentScore_ += 50;
        break;
    case GameEventType::PowerUpPicked:
        currentScore_ += 100;
        break;
    case GameEventType::EnemyKilled:
        currentScore_ += 500;
        break;
    case GameEventType::PlayerWon:
        currentScore_ += 1000;
        break;
    case GameEventType::PlayerLost:
        currentScore_ -= 250;
        break;
    }
}

void Score::updateAliveTime(const double deltaTime) {
    if (deltaTime > 0.0) {
        currentScore_ += static_cast<int>(deltaTime * 10.0);
    }
}

void Score::finishRun() {
    highscores_.push_back(currentScore_);
    std::sort(highscores_.begin(), highscores_.end(), std::greater<>());
    if (highscores_.size() > kMaxHighscores) {
        highscores_.resize(kMaxHighscores);
    }
    persistHighscores();
}

void Score::loadHighscores() {
    highscores_.clear();
    std::ifstream in(highscoresPath_);
    int value = 0;
    while (in >> value) {
        highscores_.push_back(value);
    }
    std::sort(highscores_.begin(), highscores_.end(), std::greater<>());
    if (highscores_.size() > kMaxHighscores) {
        highscores_.resize(kMaxHighscores);
    }
}

void Score::persistHighscores() const {
    std::ofstream out(highscoresPath_, std::ios::trunc);
    for (const auto score : highscores_) {
        out << score << '\n';
    }
}

} // namespace bomberman
