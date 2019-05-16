#ifndef PLAYER_H
#define PLAYER_H
#include "Ball.h"
class Player {
private:
    //int test;
public:
    Player();
    ~Player();
    void aimSetup(Ball cueBall);
};
#endif