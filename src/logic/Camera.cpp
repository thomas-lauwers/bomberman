#include "../../include/logic/Camera.h"
#include "../../include/logic/World.h"

NormalizedPosition Camera::gridToNormalized(const int x, const int y) {
    const float normX = -1.0f + (static_cast<float>(x) * 2.0f) / (World::WIDTH);
    const float normY = -1.0f + (static_cast<float>(y) * 2.0f) / (World::HEIGHT);
    return {normX, normY};
}

NormalizedPosition Camera::worldToNormalized(const float x, const float y) {
    const float normX = -1.0f + (x * 2.0f) / (static_cast<float>(World::WIDTH));
    const float normY = -1.0f + (y * 2.0f) / (static_cast<float>(World::HEIGHT));
    return {normX, normY};
}

PixelPosition Camera::normalizedToPixel(const NormalizedPosition normPos, const int winW, const int winH) {
    const float pixelX = ((normPos.x + 1.0f) / 2.0f) * static_cast<float>(winW);
    const float pixelY = ((normPos.y + 1.0f) / 2.0f) * static_cast<float>(winH);
    return {pixelX, pixelY};
}
