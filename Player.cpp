#include "Player.h"
int ballSuit, playersBallsLeft, playerNum;
bool ballSunk;
Player::Player(int playerNumber) {
    ballSuit = 0;
    playerNum = playerNumber;
    playersBallsLeft = 7;
    ballSunk = false;
}