#ifndef BOMBERMAN_EXPLOSIONVIEW_H
#define BOMBERMAN_EXPLOSIONVIEW_H
#include "../Animation.h"
#include "IEntityView.h"
#include "../../logic/factory/Explosion.h"

class TextureManager;

class ExplosionView : public IEntityView {
public:
    explicit ExplosionView(const TextureManager& t_manager, ExplosionType type);
    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;

    Animation animation;
    ExplosionType type;

    float animationTimer = 0.0f;
    size_t frameIndex = 0;
};

#endif //BOMBERMAN_EXPLOSIONVIEW_H
