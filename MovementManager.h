#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H
#include "Ball.h"
#include "Physics.h"
#include <SFML/Graphics.hpp>
#include <math.h>
bool noMovement;
extern int ballNumbers;
class MovementManager {
    public:
        void moveTick(Ball *balls[], sf::CircleShape *ballShapes[], int velocityX, int velocityY);
    private:
        float stopVelocity;
        void ballMove(Ball *ball, sf::CircleShape *ballShape);
        void collisionCheck(Ball *ball, Ball *balls[]);
};
#endif