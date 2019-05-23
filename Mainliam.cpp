#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

struct player {
    int ballSuit;
    int playersBallsLeft;
    int player;
};
    
    float finalX = 0, finalY = 0;
    int ballsLeft = 15;
    int windowWidth = 1182, windowHeight = 801;
    int tableWidth = 762, tableHeight = 381;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    sf::RectangleShape innerTable(sf:: Vector2f(tableWidth, tableHeight));
    sf::Vector2f initialPositions[] = { //array of the balls positions
        sf::Vector2f(400.5f,381.5f),  sf::Vector2f(701.5f,400.5f), sf::Vector2f(861.5f,360.5f),  sf::Vector2f(741.5f,420.5f), //0, 1, 2, 3
        sf::Vector2f(821.5f,420.5f),  sf::Vector2f(861.5f,440.5f), sf::Vector2f(781.5f,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
        sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f), sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
        sf::Vector2f(861.5f,480.5f),  sf::Vector2f(821.5f,340.5f), sf::Vector2f(781.5f,440.5f),  sf::Vector2f(821.5f,380.5f), //12, 13, 14, 15
    };
    Ball ball(1, 20.f, 400.5f, 381.f); //781.5, 400.5
    
    Ball *balls[16];
    sf::CircleShape *ballShapes[16];
    //sf::CircleShape shape(ball.radius);
    sf::CircleShape poolCue(10);

void moveBall(Ball ball, int velocityX, int velocityY){
		sf::Event event;
        while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
		}

        ball.vx = (ball.x - velocityX) * 0.005f;
        ball.vy = (ball.y - velocityY) * 0.005f;
		
        while(ball.vx != 0 || ball.vy != 0){
            
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }

            if (ball.x < 210) {
                ball.vx *= -1;
            }
            if (ball.x + ball.radius * 2 > tableWidth + 210) {
                ball.vx *= -1;
            }
            if(ball.y < 210){
                ball.vy *= -1;
            }
            if(ball.y + ball.radius*2 > tableHeight+210){
                ball.vy *= -1;
            }

            ball.ax = (-ball.vx) * 0.00075f;
            ball.ay = (-ball.vy) * 0.00075f;

            ball.vx += ball.ax;
            ball.vy += ball.ay;

            ball.x += ball.vx;
            ball.y += ball.vy;
            ballShapes[0]->setPosition(ball.x, ball.y);
            
            if(fabs(ball.vx*ball.vx + ball.vy*ball.vy) < 0.005f){
                finalX = ball.x;
                finalY = ball.y;
                ballShapes[0]->setPosition(ball.x, ball.y);
                ball.vx = 0;
                ball.vy = 0;

                poolCue.setPosition(sf::Vector2f(ball.x + ball.radius - 10, ball.y - ball.radius - 10));
            }

            window.clear();
            window.draw(innerTable);
            for(int i = 0; i < 16; i++){
                window.draw(*ballShapes[i]);
            }
            window.display();
        }
}

sf::Vector2f setPower(sf::Vector2f pos, bool elevation) {
    if(elevation) {
        pos.x += sin(0) * 0.2;
        pos.y += cos(0) * 0.2;
    } else {
        pos.x += sin(0) * -0.2;
        pos.y += cos(0) * -0.2;
    }
    return pos;
}

void playerTurn(Ball ball) {
    sf::Transform transform;
    float angle = 0.001;
    while(true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float distance = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (ball.x + ball.radius)) *
            ((poolCue.getPosition().x + poolCue.getRadius()) - (ball.x + ball.radius)) +
            ((poolCue.getPosition().y + poolCue.getRadius()) - (ball.y + ball.radius)) * 
            ((poolCue.getPosition().y + poolCue.getRadius()) - (ball.y + ball.radius)));    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            transform.rotate(poolCue.getRotation() + 0.1f, ball.x + ball.radius, ball.y + ball.radius);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            float x1 = poolCue.getPosition().x - (ball.x + (ball.radius/2));
            float y1 = poolCue.getPosition().y - (ball.y + (ball.radius / 2));

            float x2 = x1 * cos(angle) - y1 * sin(angle);
            float y2 = x1 * sin(angle) + y1 * cos(angle);

            poolCue.setPosition(x2 + (ball.x + (ball.radius / 2)), y2 + (ball.y + (ball.radius / 2)));
            //transform.rotate(poolCue.getRotation() - 0.1f, ball.x + ball.radius, ball.y + ball.radius);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (distance <= 140) {
                poolCue.setPosition(setPower(poolCue.getPosition(), false));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (distance >= 40) {
                poolCue.setPosition(setPower(poolCue.getPosition(), true));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            moveBall(ball, poolCue.getPosition().x-poolCue.getRadius(), poolCue.getPosition().y-poolCue.getRadius());
            return;
        }
        window.clear();
        window.draw(innerTable);
        for(int i = 0; i < 16; i++){
            window.draw(*ballShapes[i]);
        }
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
	// shape.setPosition(ball.x, ball.y);
	// shape.setFillColor(sf::Color::White);

	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);

    poolCue.setPosition(sf::Vector2f(ball.x + ball.radius - 10, ball.y - ball.radius - 10));
    poolCue.setFillColor(sf::Color::Black);
    for(int i = 0; i < 16; i++){
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

    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        playerTurn(ball);
        ball.x = finalX;
        ball.y = finalY;
        
        
        window.clear();
        window.draw(innerTable);
        for(int i = 0; i < 16; i++){
            window.draw(*ballShapes[i]);
        }
		//window.draw(shape);
        window.display();
	}
    return 0;
}