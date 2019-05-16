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
};
#endif