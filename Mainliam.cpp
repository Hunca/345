#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Physics.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;


int ballNumbers = 16;
int ballsLeft = 15;
int windowWidth = 1182, windowHeight = 801;
int tableWidth = 762, tableHeight = 381;
bool noMovement = true; //boolean for moving balls
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "8BallPool");
sf::RectangleShape innerTable(sf::Vector2f(tableWidth, tableHeight));
sf::RectangleShape cushions[] = {sf::RectangleShape(sf::Vector2f(336.f, 59.f)), sf::RectangleShape(sf::Vector2f(336.f, 59.f)),  // Top 2
                                 sf::RectangleShape(sf::Vector2f(59.f, 336.f)), sf::RectangleShape(sf::Vector2f(59.f, 336.f)),  // Left and right
                                 sf::RectangleShape(sf::Vector2f(336.f, 59.f)), sf::RectangleShape(sf::Vector2f(336.f, 59.f))}; // Bottom 2
sf::Vector2f cushionPositions[] = {sf::Vector2f(235.f, 151.f), sf::Vector2f(611.f, 151.f),  // Top 2
                                   sf::Vector2f(151.f, 235.f), sf::Vector2f(972.f, 235.f),  // Left and right
                                   sf::Vector2f(235.f, 591.f), sf::Vector2f(611.f, 591.f)}; // Bottom 2
Ball *balls[16];
sf::CircleShape *ballShapes[16];
sf::CircleShape poolCue(10);
sf::Vertex line[2];
sf::Clock dtClock;
float dt;
bool endTurn = false;
gameState state = PLAYERTURN;
bool screenSelected = true;
playerStruct player;
void draw(gameState state) {
    window.clear();
    window.draw(innerTable);
    for(int i = 0; i < 6; i++){
        window.draw(cushions[i]);
    }
    for(int i = 0; i < ballNumbers; i++){
        window.draw(*ballShapes[i]);
    }
    if(state == PLAYERTURN) {
        window.draw(poolCue);
        window.draw(line, 2, sf::Lines);
    }
    window.display();
}
int main() {
    GameManager::tableSetup(balls, ballShapes, ballNumbers);
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
        if(event.type == sf::Event::GainedFocus) screenSelected = true;
        if(event.type == sf::Event::LostFocus) screenSelected = false;
        
        if(state == PLAYERTURN) {
            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
            PlayerManager::playerTurn(balls[0]);
        }
        if(state == MOVEMENT) {
            MovementManager::moveTick(balls, ballShapes, poolCue.getPosition().x, poolCue.getPosition().y);
        }
        draw(state);
	}
    return 0;
}
