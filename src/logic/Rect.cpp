#include "../../include/logic/Rect.h"

bool Rect::intersects(const Rect& other) const {
    return x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y;
}
