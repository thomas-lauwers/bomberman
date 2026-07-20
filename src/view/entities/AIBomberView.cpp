#include "../../../include/view/entities/AIBomberView.h"
#include "../../../include/view/Direction.h"
#include "../../../include/view/core/TextureManager.h"

AIBomberView::AIBomberView(const TextureManager& t_manager, const BomberType type) : BomberView(t_manager), type{type} {
    configureAnimations();
}

void AIBomberView::configureAnimations() {
    int xOffset = 0;
    int yOffset = 0;

    switch (type) {
    case BomberType::Variant1:
        xOffset = 193;
        yOffset = 0;
        break;
    case BomberType::Variant2:
        xOffset = 0;
        yOffset = 258;
        break;
    case BomberType::Variant3:
        xOffset = 193;
        yOffset = 258;
        break;
    case BomberType::Player:
        break;
    }

    setupAnimations(xOffset, yOffset);
}
