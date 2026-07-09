#ifndef BOMBERMAN_VIEWPORT_UTILITY_H
#define BOMBERMAN_VIEWPORT_UTILITY_H

#include <SFML/Graphics.hpp>

class ViewportUtility {
public:
    static void setViewport(sf::RenderWindow& window, float contentAspect);
};

#endif //BOMBERMAN_VIEWPORT_UTILITY_H
