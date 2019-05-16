#include "Player.h"
#include "Ball.h"
#include <string>
#include <iostream>
#include <SFML/System.hpp>

using namespace std;

Player::Player() {
}

Player::~Player() {

}

sf::Vector2f Player::aimSetup(Ball cueBall) {
    return sf::Vector2f(cueBall.getX() + cueBall.getRadius() - 10, cueBall.getY() - cueBall.getRadius() - 10);
}