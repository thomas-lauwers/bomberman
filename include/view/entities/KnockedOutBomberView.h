#ifndef BOMBERMAN_KNOCKEDOUTBOMBERVIEW_H
#define BOMBERMAN_KNOCKEDOUTBOMBERVIEW_H
#include "../../logic/factory/BomberType.h"
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

class KnockedOutBomberView : public IEntityView {
public:
    explicit KnockedOutBomberView(const TextureManager& t_manager, BomberType type);

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;
    BomberType type;

    Animation animation;
    float animationTimer = 0.0f;
    size_t frameIndex = 0;

    float bounceTimer = 0.0f;
    float bounceDuration = 0.3f;
    float bounceAmplitude = 2.0f;
};

#endif // BOMBERMAN_KNOCKEDOUTBOMBERVIEW_H
