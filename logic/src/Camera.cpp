#include "logic/Camera.h"

namespace logic {

Camera::Camera(float windowWidth, float windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {}

void Camera::project(float normX, float normY, float& pixelX, float& pixelY) const {
    // Project normalized [-1, 1] to [0, windowSize]
    // Normalized (0,0) is center.
    // (-1, -1) is bottom-left (in SFML 0, height)
    // (1, 1) is top-right (in SFML width, 0)
    
    pixelX = (normX + 1.0f) / 2.0f * windowWidth;
    pixelY = (1.0f - normY) / 2.0f * windowHeight;
}

void Camera::setWindowSize(float width, float height) {
    windowWidth = width;
    windowHeight = height;
}

} // namespace logic
