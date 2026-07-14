#ifndef BOMBERMAN_IWORLDVIEW_H
#define BOMBERMAN_IWORLDVIEW_H

namespace sf {
    class RenderWindow;
}

class World;

class IWorldView {
public:
    virtual ~IWorldView() = default;
    virtual void render(sf::RenderWindow& window, const World& world) = 0;
    virtual void update(float deltaTime) = 0;
};

#endif //BOMBERMAN_IWORLDVIEW_H
