#include "../../../include/logic/factory/AIBomber.h"

AIBomber::AIBomber(AIBomberType type) : type{type} {}

EntityType AIBomber::getEntityType() const { return AIBomber_E; }

void AIBomber::update(float deltaTime) {
    Bomber::update(deltaTime);
    // AI logic will be implemented here later
}
