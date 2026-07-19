#ifndef BOMBERMAN_HITBOXRENDERER_H
#define BOMBERMAN_HITBOXRENDERER_H

#include <SFML/Graphics.hpp>
#include "../../logic/Camera.h"
#include "../../logic/World.h"
#include "../../logic/factory/Entity.h"
#include "../../logic/Rect.h"

extern bool showHitboxes;

inline void drawHitbox(sf::RenderWindow& window, const Entity& entity) {
    if (!showHitboxes) return;
    
    Rect collisionRect = entity.getCollisionRect();
    NormalizedPosition normPos = Camera::worldToNormalized(collisionRect.x, collisionRect.y);

    sf::RectangleShape hitbox;
    hitbox.setPosition(normPos.x, normPos.y);
    hitbox.setSize(sf::Vector2f(collisionRect.width * 2.0f / World::WIDTH, collisionRect.height * 2.0f / World::HEIGHT));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(0.005f);
    window.draw(hitbox);
}

#endif // BOMBERMAN_HITBOXRENDERER_H
