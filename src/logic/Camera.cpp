#include "../../include/logic/Camera.h"
#include "../../include/logic/World.h"

NormalizedPosition Camera::gridToNormalized(int x, int y) {
    const float normX = -1.0f + (static_cast<float>(x) * 2.0f) / (World::WIDTH);
    const float normY = -1.0f + (static_cast<float>(y) * 2.0f) / (World::HEIGHT);
    return {normX, normY};
}

PixelPosition Camera::normalizedToPixel(NormalizedPosition normPos, int winW, int winH) {
    float pixelX = ((normPos.x + 1.0f) / 2.0f) * static_cast<float>(winW);
    float pixelY = ((normPos.y + 1.0f) / 2.0f) * static_cast<float>(winH);
    return {pixelX, pixelY};
}
