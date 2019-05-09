#ifndef BALL_H
#define BALL_H
class Ball {
private:
	int num;
	float x, y, radius, speed;
public:
	Ball(int ballNum, float xPos, float yPos, float rad);
	~Ball();
	float getX();
	float getY();
	float getRadius();
};
#endif

