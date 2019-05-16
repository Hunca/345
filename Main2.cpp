#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int windowWidth = 1182, windowHeight = 801;
	int tableWidth = 762, tableHeight = 381;
	
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");

    Ball ball(1, 20.f, tableWidth / 2, tableHeight);
    Player cue;
	sf::CircleShape shape(ball.getRadius());
	shape.setPosition(ball.getX(), ball.getY());
    shape.setFillColor(sf::Color::White);

    sf::CircleShape aim(10);
    aim.setPosition(cue.aimSetup(ball));
    aim.setFillColor(sf::Color::Black);

    sf::RectangleShape innerTable(sf:: Vector2f(tableWidth, tableHeight));
	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);
    sf::Transform transform;
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
    
        float distance = sqrtf(((aim.getPosition().x + aim.getRadius()) - (shape.getPosition().x + shape.getRadius())) *
        ((aim.getPosition().x + aim.getRadius()) - (shape.getPosition().x + shape.getRadius())) +
        ((aim.getPosition().y + aim.getRadius()) - (shape.getPosition().y + shape.getRadius())) * 
        ((aim.getPosition().y + aim.getRadius()) - (shape.getPosition().y + shape.getRadius())));    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            transform = cue.rotateRight(transform, aim.getRotation(), ball.getX(), ball.getY(), ball.getRadius());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            transform = cue.rotateLeft(transform, aim.getRotation(), ball.getX(), ball.getY(), ball.getRadius());
            //transform.rotate(aim.getRotation() - 0.1f, shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (distance <= 140) {
                aim.setPosition(aim.getPosition().x + sin(0) * -0.2, aim.getPosition().y + cos(0) * -0.2);
                cue.power = distance - 40;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (distance >= 40) {
                aim.setPosition(aim.getPosition().x + sin(0) * 0.2, aim.getPosition().y + cos(0) * 0.2);
                cue.power = distance - 40;
            }
        }
        window.clear();
        window.draw(innerTable);
		window.draw(shape);
        window.draw(aim, transform);
		window.display();
	}
    return 0;
}