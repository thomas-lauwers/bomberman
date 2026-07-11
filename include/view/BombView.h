#ifndef BOMBERMAN_BOMBVIEW_H
#define BOMBERMAN_BOMBVIEW_H
#include "IEntityView.h"


class TextureManager;

class BombView : public IEntityView  {
public:
    explicit BombView(const TextureManager& t_manager);

    void draw(sf::RenderWindow& window, const Entity& entity) override;

private:
    sf::Sprite sprite;

};


#endif //BOMBERMAN_BOMBVIEW_H
