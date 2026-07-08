#ifndef BOMBERMAN_PLAYSTATE_H
#define BOMBERMAN_PLAYSTATE_H
#include "State.h"


class PlayState : public State {
public:
    void update() override;
    void render() override;
};


#endif //BOMBERMAN_PLAYSTATE_H
