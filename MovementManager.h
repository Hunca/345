#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H
#include "Ball.h"
#include "Physics.h"
#include <SFML/Graphics.hpp>
#include <math.h>
extern int ballNumbers;
extern int movingBalls;
class MovementManager {
public:
    static void moveTick(Ball *balls[], sf::CircleShape *ballShapes[], int velocityX, int velocityY);

private:
    static void ballMove(Ball *ball, sf::CircleShape *ballShape);
    static void collisionCheck(Ball *ball, Ball *balls[]);
};
#endif