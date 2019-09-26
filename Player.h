#ifndef PLAYER_H
#define PLAYER_H
class Player {
    public:
        int ballSuit;
        int playersBallsLeft;
        int playerNum;
        bool ballSunk;
        bool fouled;
        Player(int playerNumer);
};
#endif