#ifndef BOMBERMAN_CRUMBLINGWALLVIEW_H
#define BOMBERMAN_CRUMBLINGWALLVIEW_H
#include "IEntityView.h"
#include "Animation.h"

class TextureManager;

class CrumblingWallView : public IEntityView {
public:
    explicit CrumblingWallView(const TextureManager& t_manager);

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;

    Animation animation;
    float animationTimer = 0.0f;
    size_t frameIndex = 0;
};


#endif //BOMBERMAN_CRUMBLINGWALLVIEW_H