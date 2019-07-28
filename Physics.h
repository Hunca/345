#ifndef PHYSICS_H
#define PHYSICS_H
#include "Ball.h"
class Physics{
    public:
        static void boxColision(Ball ball);
        static void ballCollision(Ball ballA, Ball ballB);
};
#endif