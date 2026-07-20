#ifndef BOMBERMAN_HITBOXRENDERER_H
#define BOMBERMAN_HITBOXRENDERER_H

#include "../../logic/Camera.h"
#include "../../logic/Rect.h"
#include "../../logic/World.h"
#include "../../logic/factory/Entity.h"
#include <SFML/Graphics.hpp>

extern bool debugMode;

inline void drawHitbox(sf::RenderWindow& window, const Entity& entity) {
    if (!debugMode)
        return;

    Rect collisionRect = entity.getCollisionRect();
    NormalizedPosition normPos = Camera::worldToNormalized(collisionRect.x, collisionRect.y);

    sf::RectangleShape hitbox;
    hitbox.setPosition(normPos.x, normPos.y);
    hitbox.setSize(
        sf::Vector2f(collisionRect.width * 2.0f / World::WIDTH, collisionRect.height * 2.0f / World::HEIGHT));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(0.005f);
    window.draw(hitbox);
}

inline void drawPosition(sf::RenderWindow& window, const Entity& entity) {
    if (!debugMode)
        return;

    Position pos = entity.getPosition();
    NormalizedPosition normPos = Camera::worldToNormalized(pos.x, pos.y);

    sf::CircleShape positionMarker(0.01f);
    positionMarker.setPosition(normPos.x - 0.01f, normPos.y - 0.01f);
    positionMarker.setFillColor(sf::Color::Blue);
    window.draw(positionMarker);
}

#endif // BOMBERMAN_HITBOXRENDERER_H
