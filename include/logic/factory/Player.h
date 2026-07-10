#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

struct Position {
    float x;
    float y;
};

class Player {
public:
    Player();

    void setPosition(float x, float y);
    [[nodiscard]] Position getPosition() const;

private:
    Position position;
};


#endif //BOMBERMAN_PLAYER_H
