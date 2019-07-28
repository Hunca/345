#include "Physics.h"

//Need to change these parameters so they reference the same final value
int windowWidth = 1182, windowHeight = 801;
int tableWidth = 762, tableHeight = 381;

void Physics::boxColision(Ball ball) {
    if (ball.x <= 210)
    { //if the ball hits the left or right cushions
        ball.vx *= -1;
    }
    else if (ball.x + ball.radius * 2 >= tableWidth + 210)
    {
        ball.vx *= -1;
    }
    if (ball.y <= 210)
    { //if the ball hits the top or bottom cushions
        ball.vy *= -1;
    }
    else if (ball.y + ball.radius * 2 >= tableHeight + 210)
    {
        ball.vy *= -1;
    }
}
void Physics::ballCollision(Ball ballA, Ball ballB) {

}