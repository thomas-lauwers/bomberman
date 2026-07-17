#ifndef BOMBERMAN_BOMBERVIEW_H
#define BOMBERMAN_BOMBERVIEW_H
#include "../AnimationState.h"
#include "../BomberAnimationConfig.h"
#include "../Direction.h"
#include "IEntityView.h"
#include <SFML/Graphics.hpp>

class TextureManager;

class BomberView : public IEntityView {
public:
    explicit BomberView(const TextureManager& t_manager);
    ~BomberView() override = default;

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

protected:
    virtual void setupAnimations() = 0;

    sf::Sprite sprite;
    BomberAnimationConfig animationConfig;

    AnimationState currentAction;
    Direction currentDirection;

    float animationTimer = 0.0f;
    size_t frameIndex = 0;
};

#endif // BOMBERMAN_BOMBERVIEW_H
