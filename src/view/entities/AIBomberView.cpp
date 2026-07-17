#include "../../../include/view/entities/AIBomberView.h"
#include "../../../include/view/core/TextureManager.h"
#include "../../../include/view/Direction.h"

AIBomberView::AIBomberView(const TextureManager& t_manager, const AIBomberType type)
    : BomberView(t_manager), type{type} {
    AIBomberView::setupAnimations();
}

void AIBomberView::setupAnimations() {
    int xOffset = 0;
    int yOffset = 0;

    switch (type) {
        case AIBomberType::Variant1:
            xOffset = 193;
            yOffset = 0;
            break;
        case AIBomberType::Variant2:
            xOffset = 0;
            yOffset = 258;
            break;
        case AIBomberType::Variant3:
            xOffset = 193;
            yOffset = 258;
            break;
    }

    // Movement animations
    animationConfig.addAnimation(AnimationState::Moving, Direction::Down,
                                 {{sf::IntRect(3 + xOffset, 47 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 47 + yOffset, 16, 24), sf::IntRect(37 + xOffset, 47 + yOffset, 16, 24),
                                   sf::IntRect(20 + xOffset, 47 + yOffset, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Up,
                                 {{sf::IntRect(3 + xOffset, 97 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 97 + yOffset, 16, 24), sf::IntRect(37 + xOffset, 97 + yOffset, 16, 24),
                                   sf::IntRect(20 + xOffset, 97 + yOffset, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Left,
                                 {{sf::IntRect(3 + xOffset, 122 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 122 + yOffset, 16, 24),
                                   sf::IntRect(37 + xOffset, 122 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 122 + yOffset, 16, 24)},
                                  0.2f,
                                  true});
    animationConfig.addAnimation(AnimationState::Moving, Direction::Right,
                                 {{sf::IntRect(3 + xOffset, 72 + yOffset, 16, 24), sf::IntRect(20 + xOffset, 72 + yOffset, 16, 24), sf::IntRect(37 + xOffset, 72 + yOffset, 16, 24),
                                   sf::IntRect(20 + xOffset, 72 + yOffset, 16, 24)},
                                  0.2f,
                                  true});

    // Idle animations
    animationConfig.addAnimation(AnimationState::Idle, Direction::Down, {{sf::IntRect(20 + xOffset, 47 + yOffset, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Up, {{sf::IntRect(20 + xOffset, 97 + yOffset, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Left, {{sf::IntRect(20 + xOffset, 122 + yOffset, 16, 24)}, 1.0f, false});
    animationConfig.addAnimation(AnimationState::Idle, Direction::Right, {{sf::IntRect(20 + xOffset, 72 + yOffset, 16, 24)}, 1.0f, false});
}
