#ifndef BOMBERMAN_PLAYERVIEW_H
#define BOMBERMAN_PLAYERVIEW_H
#include "AnimationState.h"
#include "BomberAnimationConfig.h"
#include "IEntityView.h"

enum class Direction;
enum class AnimationState;
class TextureManager;

class PlayerView : public IEntityView {
public:
    explicit PlayerView(const TextureManager& t_manager);

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;

    BomberAnimationConfig animationConfig;

    AnimationState currentAction;
    Direction currentDirection;

    float animationTimer = 0.0f;
    int frameIndex = 0;
};


#endif //BOMBERMAN_PLAYERVIEW_H
