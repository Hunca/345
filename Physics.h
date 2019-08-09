#ifndef PHYSICS_H
#define PHYSICS_H
#include "Ball.h"
#include "GameManager.h"
#include <math.h>
#include <SFML/System.hpp>

extern int windowWidth, windowHeight;
extern int tableWidth, tableHeight;
extern sf::Clock dtClock;
extern float dt;

class Physics{
    public:
        static void boxColision(Ball *ball);
        static void ballCollision(Ball *ballA, Ball *ballB);
        static bool overLapDetection(Ball *whiteBall, Ball *ball);
};
#endif