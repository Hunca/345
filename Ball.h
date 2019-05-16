#ifndef BALL_H
#define BALL_H
class Ball {
private:
	int num;
public:
	float x, y, vx, vy, ax, ay, radius, speed;
	bool isSunk, isMoving;
	Ball(int ballNum, float rad, float xPos, float yPos);
	~Ball();
	float getX();
	float getY();
	float getRadius();
};
#endif

