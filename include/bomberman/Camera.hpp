#pragma once

#include "bomberman/Types.hpp"

#include <cstddef>
#include <utility>

namespace bomberman {

class Camera {
  public:
    Camera(std::size_t windowWidth, std::size_t windowHeight) : width_(windowWidth), height_(windowHeight) {}

    [[nodiscard]] std::pair<int, int> toPixel(const Vec2& normalized) const;
    [[nodiscard]] Vec2 toNormalized(int pixelX, int pixelY) const;

  private:
    std::size_t width_{1U};
    std::size_t height_{1U};
};

} // namespace bomberman
