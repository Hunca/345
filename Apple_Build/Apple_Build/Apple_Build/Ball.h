#ifndef BALL_H
#define BALL_H
class Ball {
public:
	int num;
	float x, y, vx, vy, ax, ay, radius, mass;
	bool isSunk;
	Ball(int ballNum, float rad, float xPos, float yPos);
	~Ball();
};
#endif

