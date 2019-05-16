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
    // cout << cueBall.getRadius();
    return sf::Vector2f(cueBall.getX() + cueBall.getRadius() - 10, cueBall.getY() - cueBall.getRadius());
}
sf::Vector2f Player::rotateLeft(Ball cueBall, sf::Vector2f aim) {
    return sf::Vector2f(0, 0);
}