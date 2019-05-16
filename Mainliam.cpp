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

	// while (window.isOpen())
	// {
        ball.vx = (ball.x - (ball.x-(ball.radius/10)));
        ball.vy = (ball.y - ball.y);
        printf("%f, %f", ball.vx, ball.vy);
		sf::Event event;
		
        while(ball.vx != 0 || ball.vy != 0){
            while (window.pollEvent(event))
		    {
			if (event.type == sf::Event::Closed)
				window.close();
		    }
            if(fabs(ball.vx*ball.vx + ball.vy*ball.vy) < 0.01f){
                ball.vx = 0;
                ball.vy = 0;
            }
            ball.x += ball.vx;
            ball.y += ball.vy;
            shape.setPosition(ball.x, ball.y);
           // if (shape.getPosition().x + shape.getRadius() * 2 >= tableWidth + 210) {
            if (shape.getPosition().x <= 210) {
                    ball.vx = (ball.x + +(ball.radius/10));
                    ball.vy = (ball.y - ball.y);
            }
            if (shape.getPosition().x + shape.getRadius() * 2 >= tableWidth + 210) {

                    ball.vx = (ball.x - (ball.x+(ball.radius/10)));
                    ball.vy = (ball.y - ball.y);
            }
            // if (direction == false) {
            //     shape.move(1.f, 0.f);
            //     if (shape.getPosition().x + shape.getRadius() * 2 >= tableWidth + 210) {
            //         direction = true;
            //     }
            // }
            // if (direction == true) {
            //     shape.move(-1.f, 0.f);
            //     if (shape.getPosition().x <= 210) {
            //         direction = false;
            //     }
            // }
            window.clear();
            window.draw(innerTable);
            window.draw(shape);
            window.display();
        }
		
	//}
    return 0;
}