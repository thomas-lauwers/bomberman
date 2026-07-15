#ifndef BOMBERMAN_BOMBVIEW_H
#define BOMBERMAN_BOMBVIEW_H
#include "Animation.h"
#include "IEntityView.h"


class TextureManager;

class BombView : public IEntityView  {
public:
    explicit BombView(const TextureManager& t_manager);

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;

    Animation animation;
    float animationTimer = 0.0f;
    size_t frameIndex = 0;

};


#endif //BOMBERMAN_BOMBVIEW_H
