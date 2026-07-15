#ifndef BOMBERMAN_IENTITYVIEW_H
#define BOMBERMAN_IENTITYVIEW_H

#include "../../logic/Observer.h"
#include <SFML/Graphics.hpp>

class Entity;

class IEntityView : public Observer {
public:
    ~IEntityView() override = default;

    virtual void draw(sf::RenderWindow& window, const Entity& entity) = 0;
    virtual void update(float deltaTime) = 0;
    void onNotify(const Entity& entity, Event event) override = 0;
};

#endif // BOMBERMAN_IENTITYVIEW_H
