#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

int main() {
	bool direction = false;
	int windowWidth = 1182, windowHeight = 801;
	int tableWidth = 762, tableHeight = 381;
	
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
	
	Ball ball(1, 20.f, 210.f, 210.f);
	sf::CircleShape shape(ball.getRadius());
	shape.setPosition(ball.getX(), ball.getY());
	shape.setFillColor(sf::Color::White);

	sf::RectangleShape innerTable(sf:: Vector2f(tableWidth, tableHeight));
	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);

    ball.vx = (ball.x - (ball.x-(ball.radius/20)));
    ball.vy = (ball.y - (ball.y-(ball.radius/20)));

    ball.ax = 0;
    ball.ay = 0;

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
		}
		
        while(ball.vx != 0 || ball.vy != 0){
            
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
                ball.vx = 0;
                ball.vy = 0;
            }

            window.clear();
            window.draw(innerTable);
            window.draw(shape);
            window.display();
        }
		
	}
    return 0;
}