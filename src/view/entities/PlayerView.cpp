#include "../../../include/view/entities/PlayerView.h"
#include "../../../include/logic/World.h"
#include "../../../include/logic/factory/Entity.h"
#include "../../../include/view/Direction.h"
#include "../../../include/view/core/TextureManager.h"

PlayerView::PlayerView(const TextureManager& t_manager)
    : BomberView(t_manager) {
    setupAnimations();
}

void PlayerView::setupAnimations() {
    // Movement animations
    animationConfig.addAnimation(AnimationState::Moving, Direction::Down,
                                 {{sf::IntRect(3, 47, 16, 24), sf::IntRect(20, 47, 16, 24), sf::IntRect(37, 47, 16, 24),
                                   sf::IntRect(20, 47, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Up,
                                 {{sf::IntRect(3, 97, 16, 24), sf::IntRect(20, 97, 16, 24), sf::IntRect(37, 97, 16, 24),
                                   sf::IntRect(20, 97, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Left,
                                 {{sf::IntRect(3, 122, 16, 24), sf::IntRect(20, 122, 16, 24),
                                   sf::IntRect(37, 122, 16, 24), sf::IntRect(20, 122, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Right,
                                 {{sf::IntRect(3, 72, 16, 24), sf::IntRect(20, 72, 16, 24), sf::IntRect(37, 72, 16, 24),
                                   sf::IntRect(20, 72, 16, 24)},
                                  0.2f,
                                  true});

    // Idle animations
    animationConfig.addAnimation(AnimationState::Idle, Direction::Down, {{sf::IntRect(20, 47, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Up, {{sf::IntRect(20, 97, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Left, {{sf::IntRect(20, 122, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Right, {{sf::IntRect(20, 72, 16, 24)}, 1.0f, false});
}
