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

sf::Transform Player::rotateLeft(sf::Transform transform, float rotation, float x, float y, float radius) {
    return transform.rotate(rotation - 0.1f, x + radius, y + radius);
}

sf::Transform Player::rotateRight(sf::Transform transform, float rotation, float x, float y, float radius) {
    return transform.rotate(rotation + 0.1f, x + radius, y + radius);
}

sf::Vector2f Player::aimSetup(Ball cueBall) {
    return sf::Vector2f(cueBall.getX() + cueBall.getRadius() - 10, cueBall.getY() - cueBall.getRadius() - 10);
}