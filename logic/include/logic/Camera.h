#ifndef BOMBERMAN_LOGIC_CAMERA_H
#define BOMBERMAN_LOGIC_CAMERA_H

namespace logic {

/**
 * @brief Projects normalized coordinates [-1, 1] to pixel coordinates.
 * Manual projection without SFML dependency.
 */
class Camera {
public:
    Camera(float windowWidth, float windowHeight);

    /**
     * @brief Project normalized coordinates to pixel coordinates.
     */
    void project(float normX, float normY, float& pixelX, float& pixelY) const;

    void setWindowSize(float width, float height);

private:
    float windowWidth;
    float windowHeight;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_CAMERA_H
