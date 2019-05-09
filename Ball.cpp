#include "Ball.h"
int num;
float x, y, radius, speed;
Ball::Ball(int ballNum, float xPos, float yPos, float rad) {
	num = ballNum;
	x = xPos;
	y = yPos;
	radius = rad;
}
Ball::~Ball() {

}
float Ball::getX() {
	return x;
}
float Ball::getY() {
	return y;
}
float Ball::getRadius() {
	return radius;
}