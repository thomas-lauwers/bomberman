#include "../../../include/view/core/TitleRenderer.h"

void TitleRenderer::render(IWorldView& renderer, const bool showEnter) {
    renderer.renderPortrait(300.0f, 200.0f);
    renderer.renderCenteredText("Bomberman", 100.0f);
    if (showEnter) {
        renderer.renderCenteredText("Press ENTER to Start", 200.0f);
    }


}
