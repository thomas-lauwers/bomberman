#ifndef BOMBERMAN_RECT_H
#define BOMBERMAN_RECT_H


struct Rect {
    float x;
    float y;
    float width;
    float height;

    bool intersects(const Rect& other) const;
};


#endif //BOMBERMAN_RECT_H
