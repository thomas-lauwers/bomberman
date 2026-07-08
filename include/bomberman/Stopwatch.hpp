#pragma once

#include <chrono>

namespace bomberman {

class Stopwatch {
  public:
    static Stopwatch& instance();

    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    double tick();
    double deltaTime() const noexcept { return deltaTimeSeconds_; }
    void reset();

  private:
    Stopwatch();

    std::chrono::steady_clock::time_point previous_;
    double deltaTimeSeconds_{0.0};
};

} // namespace bomberman
