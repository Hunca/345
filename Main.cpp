#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	bool direction = false;
	int windowWidth = 1182, windowHeight = 801;
	int innerTableWidth = 762, innerTableHeight = 381;
	int outerTableWidth = 870, outerTableHeight = 489;
	float outerOriginPoint = 156.6f;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");

	Ball ball(1, 210.f, 210.f, 8.55f);
	sf::CircleShape shape(ball.getRadius());
	shape.setPosition(ball.getX(), ball.getY());
	shape.setFillColor(sf::Color::White);

	sf::RectangleShape innerTable(sf::Vector2f(innerTableWidth, innerTableHeight));
	innerTable.setPosition(210.f, 210.f);
	innerTable.setFillColor(sf::Color::Green);
	//innerTable.setOutlineThickness(53.4f);
	//innerTable.setOutlineColor(sf::Color::Blue);

/**
 * Padding shapes around the table.
 */
	sf::ConvexShape firstPadW;
	firstPadW.setPointCount(4);
	firstPadW.setPoint(0, sf::Vector2f(outerOriginPoint, outerOriginPoint));
	firstPadW.setPoint(1, sf::Vector2f(outerOriginPoint + outerTableWidth / 2, outerOriginPoint));
	firstPadW.setPoint(2, sf::Vector2f(outerOriginPoint + 53.4f + innerTableWidth / 2 - 27.2f, outerOriginPoint + 53.4f));
	firstPadW.setPoint(3, sf::Vector2f(outerOriginPoint + 53.4f + 27.2f, outerOriginPoint + 53.4f));
	firstPadW.setFillColor(sf::Color::White);

	sf::ConvexShape secondPadW = firstPadW;
	secondPadW.setPoint(0, sf::Vector2f(outerOriginPoint + outerTableWidth / 2, outerOriginPoint));
	secondPadW.setPoint(1, sf::Vector2f(outerOriginPoint + outerTableWidth, outerOriginPoint));
	secondPadW.setPoint(2, sf::Vector2f(outerOriginPoint + 53.4f + innerTableWidth - 27.2f, outerOriginPoint + 53.4f));
	secondPadW.setPoint(3, sf::Vector2f(outerOriginPoint + 53.4f + innerTableWidth / 2 + 27.2f, outerOriginPoint + 53.4f));

	sf::ConvexShape firstPadW2 = firstPadW;
	firstPadW2.rotate(180);
	firstPadW2.setPosition(outerOriginPoint, outerOriginPoint);
	firstPadW2.move(outerOriginPoint + outerTableWidth, outerOriginPoint + outerTableHeight);

	sf::ConvexShape secondPadW2 = secondPadW;
	secondPadW2.rotate(180);
	secondPadW2.setPosition(outerOriginPoint + outerTableWidth / 2, outerOriginPoint);
	secondPadW2.move(outerOriginPoint + outerTableWidth / 2, outerOriginPoint + outerTableHeight);

	sf::ConvexShape firstPadH = firstPadW;
	firstPadH.setPoint(0, sf::Vector2f(outerOriginPoint, outerOriginPoint));
	firstPadH.setPoint(1, sf::Vector2f(outerOriginPoint + 53.4f, outerOriginPoint + 53.4f + 27.2f));
	firstPadH.setPoint(2, sf::Vector2f(outerOriginPoint + 53.4f, outerOriginPoint + 53.4f + innerTableHeight - 27.2f));
	firstPadH.setPoint(3, sf::Vector2f(outerOriginPoint, outerOriginPoint + outerTableHeight));

	sf::ConvexShape firstPadH2 = firstPadH;
	firstPadH2.rotate(180);
	firstPadH2.setPosition(outerOriginPoint, outerOriginPoint);
	firstPadH2.move(outerOriginPoint + outerTableWidth, outerOriginPoint + outerTableHeight);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (direction == false)
		{
			shape.move(1.f, 0.f);
			if (shape.getPosition().x + shape.getRadius() * 2 >= innerTableWidth + 210)
			{
				direction = true;
			}
		}
		if (direction == true)
		{
			shape.move(-1.f, 0.f);
			if (shape.getPosition().x <= 210)
			{
				direction = false;
			}
		}
		window.clear();

		window.draw(firstPadW);  //works
		window.draw(firstPadW2); //works

		window.draw(secondPadW);  //works
		window.draw(secondPadW2); //works

		window.draw(firstPadH); //works
		window.draw(firstPadH2);

		window.draw(innerTable);
		window.draw(shape);
		window.display();
	}
	return 0;
}