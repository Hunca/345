#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Ball.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct player {
    int ballSuit;
    int playersBallsLeft;
    int player;
};
    int ballNumbers = 16;
    int ballsLeft = 15;
    int windowWidth = 1182, windowHeight = 801;
    int tableWidth = 762, tableHeight = 381;
    bool noMovement = true; //boolean for moving balls
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    sf::RectangleShape innerTable(sf:: Vector2f(tableWidth, tableHeight));
    sf::Vector2f initialPositions[] = { //array of the balls positions
        sf::Vector2f(600.5f, 381.f),  sf::Vector2f(701.5f,400.5f), sf::Vector2f(861.5f,360.5f),  sf::Vector2f(741.5f,420.5f), //0, 1, 2, 3
        sf::Vector2f(821.5f,420.5f),  sf::Vector2f(861.5f,440.5f), sf::Vector2f(781.5f,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
        sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f), sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
        sf::Vector2f(861.5f,480.5f),  sf::Vector2f(821.5f,340.5f), sf::Vector2f(781.5f,440.5f),  sf::Vector2f(821.5f,380.5f), //12, 13, 14, 15
    };
    Ball *balls[16];
    sf::CircleShape *ballShapes[16];
    sf::CircleShape poolCue(10);
    sf::Clock dtClock;
    float dt;

    void moveBall(Ball ball, int velocityX, int velocityY)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        noMovement = false;
        balls[0]->vx = (balls[0]->x - velocityX);
        balls[0]->vy = (balls[0]->y - velocityY);

        while (!noMovement)
        {
            dt = dtClock.restart().asSeconds();
            for (int i = 0; i < ballNumbers; i++)
            {
                if (balls[i]->vx != 0 && balls[i]->vy != 0)
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }

                    if (balls[i]->x <= 210)
                    { //if the ball hits the left or right cushions
                        balls[i]->vx *= -1;
                    }
                    else if (balls[i]->x + balls[i]->radius * 2 >= tableWidth + 210)
                    {
                        balls[i]->vx *= -1;
                    }
                    if (balls[i]->y <= 210)
                    { //if the ball hits the top or bottom cushions
                        balls[i]->vy *= -1;
                    }
                    else if (balls[i]->y + balls[i]->radius * 2 >= tableHeight + 210)
                    {
                        balls[i]->vy *= -1;
                    }

                    balls[i]->ax = (-balls[i]->vx); //setting an acceloration value (friction on the table)
                    balls[i]->ay = (-balls[i]->vy);

                    balls[i]->vx += (balls[i]->ax*dt); //applying the friction to the velocity
                    balls[i]->vy += (balls[i]->ay*dt);
                    
                    // balls[i]->vx *= dt;
                    // balls[i]->vy *= dt;
                    // cout << balls[i]-> vx << " " << i << " vx\n";
                    // cout << balls[i]-> vy << " " << i << " vy\n";
                    balls[i]->x += (balls[i]->vx*dt); //moviving the ball with the velocity
                    balls[i]->y += (balls[i]->vy*dt);

                    ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);

                    for (int otherBall = 0; otherBall < ballNumbers; otherBall++)
                    {

                        if (balls[i]->num != otherBall)
                        {
                            float distanceX = (balls[i]->x - balls[otherBall]->x) * (balls[i]->x - balls[otherBall]->x);
                            float distancey = (balls[i]->y - balls[otherBall]->y) * (balls[i]->y - balls[otherBall]->y);

                            if ((distanceX + distancey) <= 1600.f)
                            { //1600.f being radius^2

                                float fDistance = sqrtf((balls[i]->x - balls[otherBall]->x) * (balls[i]->x - balls[otherBall]->x) + (balls[i]->y - balls[otherBall]->y) * (balls[i]->y - balls[otherBall]->y));
                                float distanceToMove = (balls[i]->radius + balls[otherBall]->radius) - fDistance;
                                float angle = atan2(balls[otherBall]->y - balls[i]->y, balls[otherBall]->x- balls[i]->x);
                                balls[otherBall]->y += cosf(angle) * distanceToMove;
                                balls[otherBall]->x += cosf(angle) * distanceToMove;
                                fDistance = sqrtf((balls[i]->x - balls[otherBall]->x) * (balls[i]->x - balls[otherBall]->x) + (balls[i]->y - balls[otherBall]->y) * (balls[i]->y - balls[otherBall]->y));
                                // Normal
                                float nx = (balls[otherBall]->x - balls[i]->x) / fDistance;
                                float ny = (balls[otherBall]->y - balls[i]->y) / fDistance;

                                // Tangent
                                float tx = -ny;
                                float ty = nx;

                                // Dot Product Tangent
                                float dpTan1 = balls[i]->vx * tx + balls[i]->vy * ty;
                                float dpTan2 = balls[otherBall]->vx * tx + balls[otherBall]->vy * ty;

                                // Dot Product Normal
                                float dpNorm1 = balls[i]->vx * nx + balls[i]->vy * ny;
                                float dpNorm2 = balls[otherBall]->vx * nx + balls[otherBall]->vy * ny;

                                // Conservation of momentum in 1D
                                float m1 = (dpNorm1 * (balls[i]->mass - balls[otherBall]->mass) + 2.0f * balls[otherBall]->mass * dpNorm2) / (balls[i]->mass + balls[otherBall]->mass);
                                float m2 = (dpNorm2 * (balls[otherBall]->mass - balls[i]->mass) + 2.0f * balls[i]->mass * dpNorm1) / (balls[i]->mass + balls[otherBall]->mass);

                                // Update ball velocities
                                balls[i]->vx = tx * dpTan1 + nx * m1;
                                balls[i]->vy = ty * dpTan1 + ny * m1;
                                balls[otherBall]->vx = tx * dpTan2 + nx * m2;
                                balls[otherBall]->vy = ty * dpTan2 + ny * m2;
                            }
                        }
                    }
                    cout << "fabs: " << i << ": " << fabs(balls[i]->vx * balls[i]->vx + balls[i]->vy * balls[i]->vy) << "\n";
                    if (fabs(balls[i]->vx * balls[i]->vx + balls[i]->vy * balls[i]->vy) < 1.f)
                    { //if the balls velociy gets to a certain point, stop it
                        ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);
                        balls[i]->vx = 0;
                        balls[i]->vy = 0;
                    }

                    bool currentCheck = false;
                    for (int i = 0; i < ballNumbers; i++)
                    {
                        if (balls[i]->vx != 0 && balls[i]->vy != 0 && !currentCheck)
                        {
                            currentCheck = true;
                            break;
                        }
                    }
                    if (!currentCheck)
                    {
                        noMovement = true;
                    }

                    window.clear();
                    window.draw(innerTable);
                    for (int i = 0; i < ballNumbers; i++)
                    { //redraws the balls
                        window.draw(*ballShapes[i]);
                    }
                    window.display();
                }
            }
        }
}
sf::Vertex line[2];
sf::Vector2f setPower(sf::Vector2f pos, bool elevation) {
    float delta_x = pos.x + poolCue.getRadius() - (balls[0]->x + balls[0]->radius);
    float delta_y = pos.y + poolCue.getRadius() - (balls[0]->y + balls[0]->radius);
    line[0] = sf::Vertex(sf::Vector2f(pos.x + poolCue.getRadius(), pos.y + poolCue.getRadius()), sf::Color::Black);
    line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
    float dist = sqrt((delta_x*delta_x)+(delta_y*delta_y));
    float xChange = (delta_x/dist)*(100*dt);
    float yChange = (delta_y/dist)*(100*dt);
    if(elevation) {
        pos.x -=xChange;
        pos.y -=yChange;
    } else {
        pos.x +=xChange;
        pos.y +=yChange;
    }
    return pos;
}

void playerTurn() {
    sf::Transform transform;
    float angle = 4;
    while(true) {
        sf::Event event;line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dt = dtClock.restart().asSeconds();
        float distance = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (balls[0]->x + balls[0]->radius)) *
            ((poolCue.getPosition().x + poolCue.getRadius()) - (balls[0]->x + balls[0]->radius)) +
            ((poolCue.getPosition().y + poolCue.getRadius()) - (balls[0]->y + balls[0]->radius)) * 
            ((poolCue.getPosition().y + poolCue.getRadius()) - (balls[0]->y + balls[0]->radius)));  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            float x1 = poolCue.getPosition().x - (balls[0]->x + (balls[0]->radius/2));
            float y1 = poolCue.getPosition().y - (balls[0]->y + (balls[0]->radius / 2));

            float x2 = x1 * cos(angle*dt) - y1 * sin(angle*dt);
            float y2 = x1 * sin(angle*dt) + y1 * cos(angle*dt);
            
            poolCue.setPosition(x2 + (balls[0]->x + (balls[0]->radius / 2)), y2 + (balls[0]->y + (balls[0]->radius / 2)));

            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            float x1 = poolCue.getPosition().x - (balls[0]->x + (balls[0]->radius/2));
            float y1 = poolCue.getPosition().y - (balls[0]->y + (balls[0]->radius / 2));
            float x2 = x1 * cos(-angle*dt) - y1 * sin(-angle*dt);
            float y2 = x1 * sin(-angle*dt) + y1 * cos(-angle*dt);
            

            poolCue.setPosition(x2 + (balls[0]->x + (balls[0]->radius / 2)), y2 + (balls[0]->y + (balls[0]->radius / 2)));

            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (distance <= 500) {
                poolCue.setPosition(setPower(poolCue.getPosition(), false));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (distance >= 40) {
                poolCue.setPosition(setPower(poolCue.getPosition(), true));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            moveBall(*balls[0], poolCue.getPosition().x-poolCue.getRadius(), poolCue.getPosition().y-poolCue.getRadius());
            return;
        }

        // cout << "test\n";
        window.clear();
        window.draw(innerTable);
        for(int i = 0; i < ballNumbers; i++){
            window.draw(*ballShapes[i]);
        }
        window.draw(line, 2, sf::Lines);
        window.draw(poolCue, transform);
        window.display();
    }
}

void swapPlayer(player player){
    if(player.player == 1){
        player.player = 2;
    }
    if(player.ballSuit < 8){
        player.ballSuit = 9;
    }
    player.playersBallsLeft = ballsLeft - player.playersBallsLeft - 1;
}

int main() {
	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);
    
    for(int i = 0; i < ballNumbers; i++){
        balls[i] = new Ball(i, 20.f, initialPositions[i].x, initialPositions[i].y);
        ballShapes[i] = new sf::CircleShape(balls[i]->radius);
        ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);
        if(balls[i]->num<8){
            ballShapes[i]->setFillColor(sf::Color::Blue);
        } else if(balls[i]->num>8){
            ballShapes[i]->setFillColor(sf::Color::Red);
        }
        if(balls[i]->num == 0){
            ballShapes[i]->setFillColor(sf::Color::White);
        }
        if(balls[i]->num==8){
            ballShapes[i]->setFillColor(sf::Color::Black);
        }
    }

    poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10));
    poolCue.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        playerTurn();
        poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10)); //set the pool cue.
        
        
        window.clear();
        window.draw(innerTable);
        for(int i = 0; i < ballNumbers; i++){
            window.draw(*ballShapes[i]);
        }
        window.display();
	}
    return 0;
}