#include "MovementManager.h"
#include <String>
#include <iostream>
void MovementManager::ballMove(Ball *ball, sf::CircleShape *ballShape) {
    ball->ax = (-ball->vx) * 0.5f; //setting an acceloration value (friction on the table)
    ball->ay = (-ball->vy) * 0.5f;

    ball->vx += (ball->ax * dt); //applying the friction to the velocity
    ball->vy += (ball->ay * dt);

    ball->x += (ball->vx * dt); //moviving the ball with the velocity
    ball->y += (ball->vy * dt);

    ballShape->setPosition(ball->x, ball->y);
}
bool firstCollision = true;
void MovementManager::collisionCheck(Ball *ball, Ball *balls[]) {
    for (int otherBall = 0; otherBall < ballNumbers; otherBall++) {
        if (ball->num != otherBall) {
            float distanceX = (ball->x - balls[otherBall]->x) * (ball->x - balls[otherBall]->x);
            float distancey = (ball->y - balls[otherBall]->y) * (ball->y - balls[otherBall]->y);
            if ((distanceX + distancey) <= (ball->radius*2)*(ball->radius*2)) { //diameter^2
                if((ball->vx == 0 && ball->vy == 0) || balls[otherBall]->vx == 0 && balls[otherBall]->vy == 0) {
                    movingBalls++;
                }
                Physics::ballCollision(ball, balls[otherBall]);
                if(firstCollision && ball->num == 0) {
                    firstCollision = false;
                    if(players[playerGoing]->ballSuit != 0) {
                        if(players[playerGoing]->ballSuit > 8 && balls[otherBall]->num < 8) {
                            players[playerGoing]->fouled = true;
                        } else if(players[playerGoing]->ballSuit < 8 && balls[otherBall]->num > 8) {
                            players[playerGoing]->fouled = true;
                        }
                    }
                }
            }
        }
    }
    if(ball->x+ball->radius < 230.f || ball->x+ball->radius > 952.f || ball->y+ball->radius < 230.f || ball->y+ball->radius > 571.f){
        for(int i = 0; i < 24; i++){ // 24 being the length of socketEdges. (Will always be 24)
            float edgeX = socketEdges[i][0].position.x - socketEdges[i][1].position.x;
            float edgeY = socketEdges[i][0].position.y - socketEdges[i][1].position.y;
            float edgeLength = edgeX*edgeX + edgeY*edgeY;

            float ballToLineX = ball->x+ball->radius - socketEdges[i][1].position.x;
            float ballToLineY = ball->y+ball->radius - socketEdges[i][1].position.y;

            float ballToLine = std::max((float)0, std::min(edgeLength, (edgeX * ballToLineX + edgeY * ballToLineY))) / edgeLength;
            
            float closestX = socketEdges[i][1].position.x + ballToLine * edgeX;
            float closestY = socketEdges[i][1].position.y + ballToLine * edgeY;

            float distance = sqrt((ball->x+ball->radius - closestX) * (ball->x+ball->radius - closestX) + (ball->y+ball->radius - closestY) * (ball->y+ball->radius - closestY));
            if(distance <= ball->radius){
                Physics::cushionCollision(ball, closestX, closestY);
            }
        }
    }
    if(ball->x+ball->radius < 210.f || ball->x+ball->radius > 972.f || ball->y+ball->radius < 210.f || ball->y+ball->radius > 591.f){
        for(int i = 0; i < 6; i++){ // 6 being the number of sockets. (Will always be 6)
            float socketX = socketPositions[i].x + 20.f, socketY = socketPositions[i].y + 20.f; //20.f being the radius of the socket (Will always be 20)
            if((ball->x+ball->radius-socketX)*(ball->x+ball->radius-socketX) + (ball->y+ball->radius-socketY)*(ball->y+ball->radius-socketY) <= 20*20){
                GameManager::ballSunk(ball);
            }
        }
    }
}
void MovementManager::moveTick(Ball *balls[], sf::CircleShape *ballShapes[], int velocityX, int velocityY) {
    if(movingBalls == 0) {//fires whiteBall
        // movingBalls = 0;
        balls[0]->vx = (balls[0]->x - velocityX) * 5; //times constant to alter power
        balls[0]->vy = (balls[0]->y - velocityY) * 5;
        movingBalls++;
    }
    dt = dtClock.restart().asSeconds();
    for (int i = 0; i < ballNumbers; i++) {

        if (balls[i]->vx != 0 || balls[i]->vy != 0) {
            if(balls[i]->isSunk == true) {
                balls[i]->x = -100;
                balls[i]->y = -100;
                balls[i]->ax = 0;
                balls[i]->ay = 0;
                balls[i]->vx = 0;
                balls[i]->vy = 0;
                movingBalls--;
            } else {
                //Physics::boxColision(balls[i]);
                ballMove(balls[i], ballShapes[i]);
                collisionCheck(balls[i], balls);
                if (fabs(balls[i]->vx * balls[i]->vx + balls[i]->vy * balls[i]->vy) < 50.f) { //if the balls velociy gets to a certain point, stop it
                    ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);
                    balls[i]->vx = 0;
                    balls[i]->vy = 0;
                    movingBalls--;
                }
            }
        }
        if (movingBalls < 1) {
            if(balls[0]->isSunk) {
                state = WHITEPLACEMENT;
                balls[0]->x = 591.f;
                balls[0]->y = 400.5f;
                ballShapes[0]->setPosition(balls[0]->x, balls[0]->y);
                balls[0]->isSunk = false;
                GameManager::swapPlayer();
                return;
            }
            if(firstCollision == true) {
                players[playerGoing]->fouled = true;
            }
            firstCollision = true;
            state = PLAYERTURN;
            GameManager::swapPlayer();
            poolCue.setPosition(sf::Vector2f(balls[0]->x, balls[0]->y - poolCue.getRadius()));
            return;
        }
    }
}