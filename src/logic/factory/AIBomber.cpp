#include "../../../include/logic/factory/AIBomber.h"

AIBomber::AIBomber(BomberType type) : type{type} {}

EntityType AIBomber::getEntityType() const { return AIBomber_E; }

BomberType AIBomber::getBomberType() const { return type; }

void AIBomber::update(float deltaTime) {
    Bomber::update(deltaTime);
    // AI logic will be implemented here later
}
