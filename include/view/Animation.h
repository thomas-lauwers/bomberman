#ifndef BOMBERMAN_ANIMATION_H
#define BOMBERMAN_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Animation {
    std::vector<sf::IntRect> frames;
    float duration;
    bool loop;
};

#endif // BOMBERMAN_ANIMATION_H
