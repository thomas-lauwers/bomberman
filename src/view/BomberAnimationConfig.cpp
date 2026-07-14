#include "../../include/view/BomberAnimationConfig.h"

const Animation & BomberAnimationConfig::getAnimation(AnimationState action, Direction dir) const {
    return animations.at({action, dir});
}

void BomberAnimationConfig::addAnimation(AnimationState action, Direction dir, const Animation &anim) {
    animations[{action, dir}] = anim;
}
