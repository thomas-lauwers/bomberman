#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "../../utils/Position.h"
#include "../Observer.h"
#include "../Rect.h"
#include "Entity.h"
#include "PowerUp.h"

class Player : public Entity, public Observer {
public:
    Player();

    [[nodiscard]] EntityType getEntityType() const override;

    void setPosition(float x, float y);
    [[nodiscard]] Position getPosition() const override;

    void move(float dx, float dy);

    [[nodiscard]] Rect getCollisionRect() const override;

    void onNotify(const Entity& entity, Event event) override;

    [[nodiscard]] bool canPlaceBomb() const;

    void placeBomb();

    [[nodiscard]] int getBlastRadius() const;

    void gainPowerUp(PowerUpType type);

    void triggerEvent(Event event);

    void update(float deltaTime) override;

private:
    Position position{1.0f, 1.0f};
    float speed = 4.0f; // units per second
    bool isMoving = false;
    bool wasMoving = false;

    int number_of_bombs = 2;
    float bomb_cooldown_timer = 0.0f;
    const float BOMB_COOLDOWN = 0.2f;

    int blast_radius = 1;
};

#endif // BOMBERMAN_PLAYER_H
