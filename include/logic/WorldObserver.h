#ifndef BOMBERMAN_WORLDOBSERVER_H
#define BOMBERMAN_WORLDOBSERVER_H
#include "Observer.h"
#include "World.h"
#include "factory/Entity.h"

class WorldObserver : public Observer {
    World& world;
public:
    explicit WorldObserver(World& w) : world(w) {}
    void onNotify(const Entity& entity, const Event event) override {
        if (event == Event::BombExploded) {
            world.spawnExplosion(entity.getPosition().x, entity.getPosition().y);
        }
    }
};
#endif //BOMBERMAN_WORLDOBSERVER_H
