#ifndef BOMBERMAN_TITLESTATE_H
#define BOMBERMAN_TITLESTATE_H
#include "State.h"

class TitleState : public State {
public:
    void handleInput() override;
    void update() override;
    void render() override;
};


#endif //BOMBERMAN_TITLESTATE_H
