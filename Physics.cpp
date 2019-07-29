#include "Physics.h"

void Physics::boxColision(Ball *ball) {
    if (ball->x <= 210)
    { //if the ball hits the left or right cushions
        ball->vx *= -1;
    }
    else if (ball->x + ball->radius * 2 >= tableWidth + 210)
    {
        ball->vx *= -1;
    }
    if (ball->y <= 210)
    { //if the ball hits the top or bottom cushions
        ball->vy *= -1;
    }
    else if (ball->y + ball->radius * 2 >= tableHeight + 210)
    {
        ball->vy *= -1;
    }
}
void Physics::ballCollision(Ball *ballA, Ball *ballB) {
    
    //ballPenetrationHandler
    float fDistance = sqrtf((ballA->x - ballB->x) * (ballA->x - ballB->x) + (ballA->y - ballB->y) * (ballA->y - ballB->y));
    float distanceToMove = fDistance - ballA->radius - ballB->radius;
    ballA->x -= (distanceToMove*0.5f) * (ballA->x - ballB->x) / fDistance;
    ballA->y -= (distanceToMove*0.5f) * (ballA->y - ballB->y) / fDistance;
    ballB->x += (distanceToMove*0.5f) * (ballA->x - ballB->x) / fDistance;
    ballB->y += (distanceToMove*0.5f) * (ballA->y - ballB->y) / fDistance;
    
    // Normal
    float nx = (ballB->x - ballA->x) / fDistance;
    float ny = (ballB->y - ballA->y) / fDistance;

    // Tangent
    float tx = -ny;
    float ty = nx;

    // Dot Product Tangent
    float dpTan1 = ballA->vx * tx + ballA->vy * ty;
    float dpTan2 = ballB->vx * tx + ballB->vy * ty;

    // Dot Product Normal
    float dpNorm1 = ballA->vx * nx + ballA->vy * ny;
    float dpNorm2 = ballB->vx * nx + ballB->vy * ny;

    // Conservation of momentum in 1D
    float m1 = (dpNorm1 * (ballA->mass - ballB->mass) + 2.0f * ballB->mass * dpNorm2) / (ballA->mass + ballB->mass);
    float m2 = (dpNorm2 * (ballB->mass - ballA->mass) + 2.0f * ballA->mass * dpNorm1) / (ballA->mass + ballB->mass);

    // Update ball velocities
    ballA->vx = tx * dpTan1 + nx * m1;
    ballA->vy = ty * dpTan1 + ny * m1;
    ballB->vx = tx * dpTan2 + nx * m2;
    ballB->vy = ty * dpTan2 + ny * m2;
}
