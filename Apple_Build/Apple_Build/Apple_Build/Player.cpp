#include "Player.h"
#include "Ball.h"
#include <string>
#include <iostream>
#include <math.h>
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
    return sf::Vector2f(cueBall.x + cueBall.radius - 10, cueBall.y - cueBall.radius - 10);
}

sf::Vector2f Player::setPower(sf::Vector2f pos, bool elevation) {
    if(elevation) {
        pos.x += sin(0) * 0.2;
        pos.y += cos(0) * 0.2;
    } else {
        pos.x += sin(0) * -0.2;
        pos.y += cos(0) * -0.2;
    }
    return pos;
}