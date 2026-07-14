#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H

#include "State.h"
#include "../World.h"
#include "../Input.h"
#include "../IWorldView.h"
#include "../WorldObserver.h"
#include <memory>
#include <vector>

class IEntityFactory;

class PlayState : public State {
public:
    ~PlayState() override;
    explicit PlayState(std::shared_ptr<IEntityFactory> factory);

    void handleInput(Input input) override;

    void update(float deltaTime, IWorldView& renderer) override;
    void render(sf::RenderWindow& window, IWorldView& renderer) override;
    [[nodiscard]] const World& getWorld() const { return world; }

private:
    std::shared_ptr<IEntityFactory> factory;
    World world;
    std::vector<std::shared_ptr<WorldObserver>> bombObservers;
};


#endif //BOMBERMAN_PLAYSTATE_H
