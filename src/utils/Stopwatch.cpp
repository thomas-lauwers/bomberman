#include "../../include/utils/Stopwatch.h"

void Stopwatch::update() {
    const auto currentTick = std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsed = currentTick - lastTick;
    deltaTime = elapsed.count();
    lastTick = currentTick;
}

double Stopwatch::getDeltaTime() const { return deltaTime; }

Stopwatch::Stopwatch(): lastTick(std::chrono::steady_clock::now()), deltaTime(0.0) {}
