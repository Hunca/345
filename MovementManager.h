#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H
#include "Ball.h"
#include "Physics.h"
#include <math.h>
bool noMovement;
class MovementManager {
    void moveBall2(Ball *balls[], int velocityX, int velocityY);
};
#endif