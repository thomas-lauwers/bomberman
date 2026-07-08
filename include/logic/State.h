#ifndef BOMBERMAN_STATE_H
#define BOMBERMAN_STATE_H


class State {
public:
    virtual ~State() = default;

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};


#endif //BOMBERMAN_STATE_H
