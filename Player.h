#ifndef PLAYER_H
#define PLAYER_H
#include "Ball.h"
#include <SFML/System.hpp>
class Player {
private:
    int power;
    
public:
    Player();
    ~Player();
    sf::Vector2f aimSetup(Ball cueBall);
    sf::Vector2f rotateLeft(Ball cueBall, sf::Vector2f aim);
};
#endif