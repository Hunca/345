#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	bool direction = false;
	int windowWidth = 1182, windowHeight = 801;
	int tableWidth = 762, tableHeight = 381;
	
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
	
	Ball ball(1, 210.f, 210.f, 20.f);
	sf::CircleShape shape(ball.getRadius());
	shape.setPosition(ball.getX(), ball.getY());
	shape.setFillColor(sf::Color::White);

	sf::RectangleShape innerTable(sf:: Vector2f(tableWidth, tableHeight));
	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);

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
			if (shape.getPosition().x + shape.getRadius() * 2 >= tableWidth + 210) {
				direction = true;
			}
		}
		if (direction == true) {
			shape.move(-1.f, 0.f);
			if (shape.getPosition().x <= 210) {
				direction = false;
			}
		}
		window.clear();
		window.draw(innerTable);
		window.draw(shape);
		window.display();
	}
    return 0;
}