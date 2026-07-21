/**
 * @file BomberAnimationConfig.h
 * @brief Defines the BomberAnimationConfig class for mapping animation states to animation sequences.
 */

#ifndef BOMBERMAN_BOMBERANIMATIONCONFIG_H
#define BOMBERMAN_BOMBERANIMATIONCONFIG_H
#include "Animation.h"
#include "AnimationState.h"
#include "Direction.h"
#include <map>

/**
 * @class BomberAnimationConfig
 * @brief Manages the configuration of animations for bomber characters.
 */
class BomberAnimationConfig {
public:
    /**
     * @brief Gets the animation sequence for a specific action and direction.
     * @param action The animation action (Idle/Moving).
     * @param dir The direction of movement.
     * @return Const reference to the animation.
     */
    [[nodiscard]] const Animation& getAnimation(AnimationState action, Direction dir) const;
    
    /**
     * @brief Adds an animation sequence for a specific action and direction.
     * @param action The animation action (Idle/Moving).
     * @param dir The direction of movement.
     * @param anim The animation sequence to add.
     */
    void addAnimation(AnimationState action, Direction dir, const Animation& anim);

private:
    std::map<std::pair<AnimationState, Direction>, Animation> animations; ///< Map of action-direction pairs to animations
};

#endif // BOMBERMAN_BOMBERANIMATIONCONFIG_H
