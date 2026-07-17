#include "../../../include/view/entities/PlayerView.h"

PlayerView::PlayerView(const TextureManager& t_manager)
    : BomberView(t_manager) {
    setupAnimations(0, 0);
}
