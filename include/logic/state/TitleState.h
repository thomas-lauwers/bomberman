#ifndef BOMBERMAN_TITLESTATE_H
#define BOMBERMAN_TITLESTATE_H
#include "State.h"
#include "../Score.h"
#include <functional>
#include <vector>

class TitleState : public State {
public:
    explicit TitleState(std::function<void()> onSelect);
    ~TitleState() override;

    void handleInput(Input input) override;

    void update(float deltaTime, IWorldView& renderer) override;
    void render(IWorldView& renderer) override;

private:
    float blinkTimer = 0.0f;
    bool showText = true;
    std::function<void()> onSelect;
    Score score;
};

#endif // BOMBERMAN_TITLESTATE_H
