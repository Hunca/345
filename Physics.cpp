#include "Physics.h"
#include "iostream"
using namespace std;

void Physics::boxColision(Ball *ball) {

    if(ball->x+ball->radius < 230.f || ball->x+ball->radius > 952.f || ball->y+ball->radius < 230.f || ball->y+ball->radius > 571.f)
    {
        for(int i = 0; i < 18; i++) // 18 being the length of socketEdges.
        {
            float edgeX = socketEdges[i][0].position.x - socketEdges[i][1].position.x;
            float edgeY = socketEdges[i][0].position.y - socketEdges[i][1].position.y;
            float edgeLength = edgeX*edgeX + edgeY*edgeY;

            float ballToLineX = ball->x+ball->radius - socketEdges[i][1].position.x;
            float ballToLineY = ball->y+ball->radius - socketEdges[i][1].position.y;

            float ballToLine = max((float)0, min(edgeLength, (edgeX * ballToLineX + edgeY * ballToLineY))) / edgeLength;
            
            float closestX = socketEdges[i][1].position.x + ballToLine * edgeX;
            float closestY = socketEdges[i][1].position.y + ballToLine * edgeY;

            float distance = sqrt((ball->x+ball->radius - closestX) * (ball->x+ball->radius - closestX) + (ball->y+ball->radius - closestY) * (ball->y+ball->radius - closestY));
            
            for (int checkCorner = 0; checkCorner < 12; checkCorner++) {
                    float distanceX = (ball->x - cornerObjects[checkCorner]->x) * (ball->x - cornerObjects[checkCorner]->x);
                    float distancey = (ball->y - cornerObjects[checkCorner]->y) * (ball->y - cornerObjects[checkCorner]->y);
                    if ((distanceX + distancey) <= (ball->radius*2)*(8.55f*2)) { //1600.f being radius^2
                        cout << "swag g";
                        Physics::cushionCollision(ball, cornerObjects[checkCorner]);
                        Ball *tempBall = cornerObjects[checkCorner];
                        
                        // cornerObjects[checkCorner]->vx = 0;
                        // cornerObjects[checkCorner]->vy = 0;
                        // cornerObjects[checkCorner] = tempBall;
                    }
            }

            if(distance <= ball->radius){
                ball->vx *= -1;
                ball->vy *= -1;
            }
        }
    }

    // if (ball->x <= 210)
    // { //if the ball hits the left or right cushions
    //     ball->x=211;
    //     ball->vx *= -1;
    // }
    // else if (ball->x + ball->radius * 2 >= tableWidth + 210)
    // {
    //     ball->x = 971 - (ball->radius * 2);
    //     ball->vx *= -1;
    // }
    // if (ball->y <= 210)
    // { //if the ball hits the top or bottom cushions
    //     ball->y = 211;
    //     ball->vy *= -1;
    // }
    // else if (ball->y + ball->radius * 2 >= tableHeight + 210)
    // {
    //     ball->y = 590 - (ball->radius * 2);
    //     ball->vy *= -1;
    // }
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

void Physics::cushionCollision(Ball *ballA, Ball *ballB) {
    
    //ballPenetrationHandler
    float fDistance = sqrtf((ballA->x - ballB->x) * (ballA->x - ballB->x) + (ballA->y - ballB->y) * (ballA->y - ballB->y));
    float distanceToMove = fDistance - ballA->radius - ballB->radius;
    ballA->x -= (distanceToMove) * (ballA->x - ballB->x) / fDistance;
    ballA->y -= (distanceToMove) * (ballA->y - ballB->y) / fDistance;
    
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
}