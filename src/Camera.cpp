#include "bomberman/Camera.hpp"

#include <algorithm>

namespace bomberman {

std::pair<int, int> Camera::toPixel(const Vec2& normalized) const {
    const auto clampedX = std::clamp(normalized.x, -1.0, 1.0);
    const auto clampedY = std::clamp(normalized.y, -1.0, 1.0);

    const int x = static_cast<int>(((clampedX + 1.0) / 2.0) * static_cast<double>(width_ - 1U));
    const int y = static_cast<int>(((clampedY + 1.0) / 2.0) * static_cast<double>(height_ - 1U));
    return {x, y};
}

Vec2 Camera::toNormalized(const int pixelX, const int pixelY) const {
    const auto safeWidth = std::max<std::size_t>(1U, width_ - 1U);
    const auto safeHeight = std::max<std::size_t>(1U, height_ - 1U);

    return {
        (2.0 * static_cast<double>(pixelX) / static_cast<double>(safeWidth)) - 1.0,
        (2.0 * static_cast<double>(pixelY) / static_cast<double>(safeHeight)) - 1.0,
    };
}

} // namespace bomberman
