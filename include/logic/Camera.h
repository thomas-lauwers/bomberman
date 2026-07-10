#ifndef BOMBERMAN_CAMERA_H
#define BOMBERMAN_CAMERA_H

struct NormalizedPosition {
    float x; // range [-1, 1]
    float y; // range [-1, 1]
};

struct PixelPosition {
    float x;
    float y;
};

class Camera {
public:
    static NormalizedPosition gridToNormalized(int x, int y);
    static NormalizedPosition worldToNormalized(float x, float y);
    static PixelPosition normalizedToPixel(NormalizedPosition normPos, int winW, int winH);
};


#endif //BOMBERMAN_CAMERA_H
