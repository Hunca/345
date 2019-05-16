#include "Player.h"
#include "Ball.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player() {
}

Player::~Player() {

}

void Player::aimSetup(Ball cueBall) {
    cout << cueBall.getRadius();
}