/**
 * @file Rect.h
 * @brief Defines the Rect struct for bounding box calculations.
 */

#ifndef BOMBERMAN_RECT_H
#define BOMBERMAN_RECT_H

/**
 * @struct Rect
 * @brief Represents a rectangle for collision detection and bounding boxes.
 */
struct Rect {
    float x;      ///< Top-left x coordinate
    float y;      ///< Top-left y coordinate
    float width;  ///< Width of the rectangle
    float height; ///< Height of the rectangle

    /**
     * @brief Checks if this rectangle intersects with another rectangle.
     * @param other The other rectangle to check against.
     * @return True if they intersect, false otherwise.
     */
    [[nodiscard]] bool intersects(const Rect& other) const;
};

#endif // BOMBERMAN_RECT_H
