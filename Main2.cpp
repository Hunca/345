#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;
int windowWidth = 1182, windowHeight = 801;
int tableWidth = 762, tableHeight = 381;

sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
sf::Vector2f aimSetup(Ball cueBall) {
    return sf::Vector2f(cueBall.getX() + cueBall.getRadius() - 10, cueBall.getY() - cueBall.getRadius() - 10);
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

sf::Vector2f playerTurn(Ball ball, sf::CircleShape aim, sf::RectangleShape innerTable, sf::CircleShape shape) {
    sf::Transform transform;
    while(true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float distance = sqrtf(((aim.getPosition().x + aim.getRadius()) - (ball.x + ball.getRadius())) *
            ((aim.getPosition().x + aim.getRadius()) - (ball.x + ball.radius)) +
            ((aim.getPosition().y + aim.getRadius()) - (ball.y + ball.radius)) * 
            ((aim.getPosition().y + aim.getRadius()) - (ball.y + ball.radius)));    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            transform.rotate(aim.getRotation() + 0.1f, ball.x + ball.radius, ball.y + ball.radius);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            transform.rotate(aim.getRotation() - 0.1f, ball.x + ball.radius, ball.y + ball.radius);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (distance <= 140) {
                aim.setPosition(setPower(aim.getPosition(), false));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (distance >= 40) {
                aim.setPosition(setPower(aim.getPosition(), true));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            return aim.getPosition();
        }
        window.clear();
        window.draw(innerTable);
        window.draw(shape);
        window.draw(aim, transform);
        window.display();
    }
}
int main() {
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
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        playerTurn(ball, aim, innerTable, shape);
        // moveBall(ball );
        window.clear();
        window.draw(innerTable);
		window.draw(shape);
        window.display();
	}
    return 0;
}