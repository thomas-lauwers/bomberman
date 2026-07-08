#include "logic/Stopwatch.h"

namespace logic {

Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

Stopwatch::Stopwatch() : deltaTime(0.0f) {
    reset();
}

float Stopwatch::getDeltaTime() const {
    return deltaTime;
}

void Stopwatch::tick() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - lastTime;
    lastTime = now;
    deltaTime = elapsed.count();
}

void Stopwatch::reset() {
    lastTime = std::chrono::steady_clock::now();
    deltaTime = 0.0f;
}

} // namespace logic
