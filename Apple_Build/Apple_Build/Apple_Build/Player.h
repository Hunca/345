#ifndef PLAYER_H
#define PLAYER_H
#include "Ball.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class Player {
private:
    //int power;
    
public:
    int power;
    Player();
    ~Player();
    sf::Vector2f aimSetup(Ball cueBall);
    sf::Transform rotateLeft(sf::Transform transform, float rotation, float x, float y, float radius);
    sf::Transform rotateRight(sf::Transform transform, float rotation, float x, float y, float radius);
    sf::Vector2f setPower(sf::Vector2f pos, bool elevation);
};
#endif