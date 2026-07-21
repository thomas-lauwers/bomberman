/**
 * @file Camera.h
 * @brief Defines utility structures and the Camera class for coordinate transformations.
 */

#ifndef BOMBERMAN_CAMERA_H
#define BOMBERMAN_CAMERA_H

/**
 * @struct NormalizedPosition
 * @brief Represents a position in a normalized coordinate system ([-1, 1] range).
 */
struct NormalizedPosition {
    float x; ///< X coordinate in [-1, 1]
    float y; ///< Y coordinate in [-1, 1]
};

/**
 * @struct PixelPosition
 * @brief Represents a position in pixel screen coordinates.
 */
struct PixelPosition {
    float x; ///< X pixel coordinate
    float y; ///< Y pixel coordinate
};

/**
 * @class Camera
 * @brief Provides utility methods for transforming between different coordinate systems.
 */
class Camera {
public:
    /**
     * @brief Transforms grid coordinates to normalized coordinates.
     * @param x Grid X coordinate.
     * @param y Grid Y coordinate.
     * @return Normalized position.
     */
    static NormalizedPosition gridToNormalized(int x, int y);

    /**
     * @brief Transforms world coordinates to normalized coordinates.
     * @param x World X coordinate.
     * @param y World Y coordinate.
     * @return Normalized position.
     */
    static NormalizedPosition worldToNormalized(float x, float y);

    /**
     * @brief Transforms normalized coordinates to pixel coordinates.
     * @param normPos Normalized position.
     * @param winW Window width.
     * @param winH Window height.
     * @return Pixel position.
     */
    static PixelPosition normalizedToPixel(NormalizedPosition normPos, int winW, int winH);
};

#endif // BOMBERMAN_CAMERA_H
