#include "MovementManager.h"
bool noMovement = true;
void MovementManager::moveBall2(Ball *balls[], int velocityX, int velocityY) {
    if(noMovement) {
        noMovement = false;
        balls[0]->vx = (balls[0]->x - velocityX);
        balls[0]->vy = (balls[0]->y - velocityY);
    }
    dt = dtClock.restart().asSeconds();
    
}