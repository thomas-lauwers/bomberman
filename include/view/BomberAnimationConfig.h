#ifndef BOMBERMAN_BOMBERANIMATIONCONFIG_H
#define BOMBERMAN_BOMBERANIMATIONCONFIG_H
#include "Animation.h"
#include "AnimationState.h"
#include "Direction.h"

class BomberAnimationConfig {
public:
    [[nodiscard]] const Animation& getAnimation(AnimationState action, Direction dir) const;
    void addAnimation(AnimationState action, Direction dir, const Animation& anim);

private:
    std::map<std::pair<AnimationState, Direction>, Animation> animations;
};

#endif // BOMBERMAN_BOMBERANIMATIONCONFIG_H
