#ifndef BOMBERMAN_IENTITYVIEW_H
#define BOMBERMAN_IENTITYVIEW_H

#include <SFML/Graphics.hpp>

class Entity;

class IEntityView {
public:
    virtual ~IEntityView() = default;

    virtual void draw(sf::RenderWindow& window, const Entity& entity) = 0;

};


#endif //BOMBERMAN_IENTITYVIEW_H
