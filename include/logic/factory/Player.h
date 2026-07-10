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

    void move(float dx, float dy);

private:
    Position position;
    float speed; // units per second
};


#endif //BOMBERMAN_PLAYER_H
