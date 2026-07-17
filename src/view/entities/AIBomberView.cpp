#include "../../../include/view/entities/AIBomberView.h"
#include "../../../include/view/core/TextureManager.h"
#include "../../../include/view/Direction.h"

AIBomberView::AIBomberView(const TextureManager& t_manager, const AIBomberType type)
    : BomberView(t_manager), type{type} {
    configureAnimations();
}

void AIBomberView::configureAnimations() {
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

    BomberView::setupAnimations(xOffset, yOffset);
}
