#ifndef BOMBERMAN_POWERUPVIEW_H
#define BOMBERMAN_POWERUPVIEW_H
#include "../../logic/factory/PowerUp.h"
#include "../Animation.h"
#include "IEntityView.h"

class TextureManager;

class PowerUpView : public IEntityView {
public:
    explicit PowerUpView(const TextureManager& t_manager, PowerUpType type);

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;

    Animation animation;
    PowerUpType type;

    float animationTimer = 0.0f;
    size_t frameIndex = 0;
};

#endif // BOMBERMAN_POWERUPVIEW_H
