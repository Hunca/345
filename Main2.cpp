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
    bool direction = false;
    Ball ball(1, 20.f, 525.f, 525.f);
    sf::CircleShape shape(ball.getRadius());
    sf::CircleShape poolCue(10);

void moveBall(Ball ball, int velocityX, int velocityY){
    // ball.vx = 0;
    // ball.vy = 0;

    // ball.ax = 0;
    // ball.ay = 0;

		sf::Event event;
        while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
		}
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        //     ball.vx = (ball.x - (ball.x-(ball.radius/20)));
        //     ball.vy = (ball.y - (ball.y-(ball.radius/20)));
        // }

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
            shape.setPosition(ball.x, ball.y);
            
            if(fabs(ball.vx*ball.vx + ball.vy*ball.vy) < 0.005f){
                finalX = ball.x;
                finalY = ball.y;
                shape.setPosition(ball.x, ball.y);
                ball.vx = 0;
                ball.vy = 0;

                poolCue.setPosition(sf::Vector2f(ball.getX() + ball.getRadius() - 10, ball.getY() - ball.getRadius() - 10));
            }

            window.clear();
            window.draw(innerTable);
            window.draw(shape);
            window.display();
        }
}

sf::Vector2f setPower(sf::Vector2f pos, bool elevation) {
    // float delta_x = pos.x - (ball.x);
    // float delta_y = pos.y - (ball.x);
    // float r = atan2(delta_y, delta_x);
    printf("cue  %f %f\n", pos.x, pos.y);
    printf("ball  %f %f\n", ball.x, ball.y);
    if(elevation) {
        pos.x += (ball.x - (pos.x-10)) * 0.005;
        pos.y += (ball.y - (pos.y-10)) * 0.005;
        // pos.x += sin(r) * 0.2;
        // pos.y += cos(r) * 0.2;
    } else {
        pos.x -= (ball.x - (pos.x - 10)) * 0.005;
        pos.y -= (ball.y - (pos.y - 10)) * 0.005;
        // pos.x += sin(r) * -0.2;
        // pos.y += cos(r) * -0.2;
    }
    
    return pos;
}

void playerTurn(Ball ball) {
    sf::Transform transform;
    float angle = 0.005;
    while(true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float distance = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (ball.x + ball.getRadius())) *
            ((poolCue.getPosition().x + poolCue.getRadius()) - (ball.x + ball.radius)) +
            ((poolCue.getPosition().y + poolCue.getRadius()) - (ball.y + ball.radius)) * 
            ((poolCue.getPosition().y + poolCue.getRadius()) - (ball.y + ball.radius)));    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            float x1 = poolCue.getPosition().x - (ball.x + (ball.radius/2));
            float y1 = poolCue.getPosition().y - (ball.y + (ball.radius / 2));

            float x2 = x1 * cos(angle) - y1 * sin(angle);
            float y2 = x1 * sin(angle) + y1 * cos(angle);
            // printf("%f yeet \n", distance);
            poolCue.setPosition(x2 + (ball.x + (ball.radius / 2)), y2 + (ball.y + (ball.radius / 2)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            float x1 = poolCue.getPosition().x - (ball.x + (ball.radius/2));
            float y1 = poolCue.getPosition().y - (ball.y + (ball.radius / 2));

            float x2 = x1 * cos(-angle) - y1 * sin(-angle);
            float y2 = x1 * sin(-angle) + y1 * cos(-angle);
            // printf("%f yeet \n", distance);
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
        window.draw(shape);
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
	shape.setPosition(ball.getX(), ball.getY());
	shape.setFillColor(sf::Color::White);

	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);

    poolCue.setPosition(sf::Vector2f(ball.getX() + ball.getRadius() - 10, ball.getY() - ball.getRadius() - 10));
    poolCue.setFillColor(sf::Color::Black);

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
		window.draw(shape);
        window.display();
	}
    return 0;
}