#include "Player.h"
int ballSuit, playersBallsLeft, playerNum;
bool ballSunk, fouled;
Player::Player(int playerNumber) {
    ballSuit = 0;
    playerNum = playerNumber;
    playersBallsLeft = 7;
    ballSunk = false;
    fouled = false;
}