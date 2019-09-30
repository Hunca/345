#include "Ball.h"
int num;
float x, y, vx, vy, ax, ay, radius, mass;
bool isSunk;

Ball::Ball(int ballNum, float rad, float xPos, float yPos) {
	num = ballNum;
	x = xPos; y = yPos;
	vx = 0; vy = 0;
	ax = 0; ay = 0;
	radius = rad;
	isSunk = false;
	mass = radius * 10.f;
}
Ball::~Ball() {
}