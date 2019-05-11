#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	bool direction = false;
	int windowWidth = 870, windowHeight = 489;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
	Ball ball(1, 20.f, 20.f, 20.f);
	sf::CircleShape shape(ball.getRadius());
	shape.setPosition(ball.getX(), ball.getY());
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (direction == false) {
			shape.move(1.f, 0.f);
			if (shape.getPosition().x + shape.getRadius() * 2 >= windowWidth) {
				direction = true;
			}
		}
		if (direction == true) {
			shape.move(-1.f, 0.f);
			if (shape.getPosition().x <= 0) {
				direction = false;
			}
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
    return 0;
}