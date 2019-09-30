#include "Physics.h"
#include "iostream"
using namespace std;

void Physics::ballCollision(Ball *ballA, Ball *ballB) {
    
    //ballPenetrationHandler
    float fDistance = sqrtf((ballA->x - ballB->x) * (ballA->x - ballB->x) + (ballA->y - ballB->y) * (ballA->y - ballB->y));
    float distanceToMove = fDistance - ballA->radius - ballB->radius;
    if(ballB->num > 0){
        ballA->x -= (distanceToMove*0.5f) * (ballA->x - ballB->x) / fDistance;
        ballA->y -= (distanceToMove*0.5f) * (ballA->y - ballB->y) / fDistance;
        ballB->x += (distanceToMove*0.5f) * (ballA->x - ballB->x) / fDistance;
        ballB->y += (distanceToMove*0.5f) * (ballA->y - ballB->y) / fDistance;
    }
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
    if(ballB->num < 0){
        ballA->x -= (distanceToMove*0.1f) * (ballA->x - ballB->x) / fDistance;
        ballA->y -= (distanceToMove*0.1f) * (ballA->y - ballB->y) / fDistance;
    }
}

void Physics::cushionCollision(Ball *ballA, float x, float y) {
    Ball *ballB = new Ball(-1, 8.55f, x, y);
    ballB->mass = ballA->mass * 0.8f;
    ballB->vx = -ballA->vx;
    ballB->vy = -ballA->vy;
    ballB->x-=ballB->radius;
    ballB->y-=ballB->radius;
    ballCollision(ballA, ballB);
    delete(ballB);
}
bool Physics::overLapDetection(Ball *whiteBall, Ball *ball) {
    float x1 = whiteBall->x + whiteBall->radius, x2 = ball->x + ball->radius;
    float y1 = whiteBall->y + whiteBall->radius, y2 = ball->y + ball->radius;
    float sumOfRadii = whiteBall->radius + ball->radius;
    float distanceSquared = ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
    if(distanceSquared  < sumOfRadii * sumOfRadii) {
        return true;
    }
    return false;
}