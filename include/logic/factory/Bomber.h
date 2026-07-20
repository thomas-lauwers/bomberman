#ifndef BOMBERMAN_BOMBER_H
#define BOMBERMAN_BOMBER_H

#include "../../utils/Position.h"
#include "../Observer.h"
#include "../Rect.h"
#include "BomberType.h"
#include "Entity.h"
#include "PowerUp.h"

class Bomber : public Entity, public Observer {
public:
    Bomber() = default;

    virtual ~Bomber() = default;

    [[nodiscard]] virtual BomberType getBomberType() const = 0;

    void setPosition(float x, float y);
    [[nodiscard]] Position getPosition() const override;

    void move(float dx, float dy);
    void moveDirectly(float dx, float dy);

    [[nodiscard]] Rect getCollisionRect() const override;

    void onNotify(const Entity& entity, Event event) override;

    [[nodiscard]] bool canPlaceBomb() const;

    void placeBomb();

    [[nodiscard]] int getBlastRadius() const;

    void gainPowerUp(PowerUpType type);

    void triggerEvent(Event event);

    void update(float deltaTime) override;

protected:
    Position position{1.5f, 1.5f};
    float speed = 4.0f; // units per second
    bool isMoving = false;
    bool wasMoving = false;

    int number_of_bombs = 1;
    float bomb_cooldown_timer = 0.0f;
    const float BOMB_COOLDOWN = 0.2f;

    int blast_radius = 1;
};

#endif // BOMBERMAN_BOMBER_H
