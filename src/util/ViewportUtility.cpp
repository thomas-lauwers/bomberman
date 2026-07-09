#include "../../include/util/ViewportUtility.h"

void ViewportUtility::setViewport(sf::RenderWindow& window, const float contentAspect) {
    sf::View view(sf::FloatRect(-1.0f, -1.0f, 2.0f, 2.0f));

    const float winW = static_cast<float>(window.getSize().x);
    const float winH = static_cast<float>(window.getSize().y);

    if (const float windowAspect = winW / winH; windowAspect > contentAspect) {
        const float viewportScale = contentAspect / windowAspect;
        view.setViewport(sf::FloatRect((1.0f - viewportScale) / 2.0f, 0, viewportScale, 1.0f));
    } else {
        const float viewportScale = windowAspect / contentAspect;
        view.setViewport(sf::FloatRect(0, (1.0f - viewportScale) / 2.0f, 1.0f, viewportScale));
    }

    window.setView(view);
}
