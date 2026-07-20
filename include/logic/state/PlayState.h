#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H

#include "../IWorldView.h"
#include "../Input.h"
#include "../World.h"
#include "State.h"
#include <memory>

class IEntityFactory;

class PlayState : public State {
public:
    ~PlayState() override;
    explicit PlayState(std::shared_ptr<IEntityFactory> factory);

    void handleInput(Input input) override;

    void update(float deltaTime, IWorldView& renderer) override;
    void render(IWorldView& renderer) override;

    bool isGameOver();

    [[nodiscard]] const World& getWorld() const { return *world; }

private:
    std::shared_ptr<IEntityFactory> factory;
    std::shared_ptr<World> world;

    bool playerWon = false;
};

#endif // BOMBERMAN_PLAYSTATE_H
