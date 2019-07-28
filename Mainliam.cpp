#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Physics.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct player {
    int ballSuit;
    int playersBallsLeft;
    int player;
};
    int ballNumbers = 16;
    int ballsLeft = 15;
    int windowWidth = 1182, windowHeight = 801;
    int tableWidth = 762, tableHeight = 381;
    bool noMovement = true; //boolean for moving balls
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "8BallPool");
    sf::RectangleShape innerTable(sf:: Vector2f(tableWidth, tableHeight));
    sf::Vector2f initialPositions[] = { //array of the balls positions
        sf::Vector2f(600.5f, 381.f),  sf::Vector2f(701.5f,400.5f), sf::Vector2f(861.5f,360.5f),  sf::Vector2f(741.5f,420.5f), //0, 1, 2, 3
        sf::Vector2f(821.5f,420.5f),  sf::Vector2f(861.5f,440.5f), sf::Vector2f(781.5f,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
        sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f), sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
        sf::Vector2f(861.5f,480.5f),  sf::Vector2f(821.5f,340.5f), sf::Vector2f(781.5f,440.5f),  sf::Vector2f(821.5f,380.5f), //12, 13, 14, 15
    };
    Ball *balls[16];
    sf::CircleShape *ballShapes[16];
    sf::CircleShape poolCue(10);
    sf::Vertex line[2];
    sf::Clock dtClock;
    float dt;

    void moveBall(int velocityX, int velocityY) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        MovementManager::moveTick(balls, ballShapes, velocityX, velocityY);
        while(movingBalls != 0) {
            MovementManager::moveTick(balls, ballShapes, velocityX, velocityY);
            window.clear();
            window.draw(innerTable);
            for (int i = 0; i < ballNumbers; i++)
            { //redraws the balls
                window.draw(*ballShapes[i]);
            }
            window.display();
        }
        
}

void playerTurn() {
    sf::Transform transform;
    float angle = 4;
    while(true) {
        sf::Event event;
        line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
        line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dt = dtClock.restart().asSeconds();
        float distance = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (balls[0]->x + balls[0]->radius)) *
            ((poolCue.getPosition().x + poolCue.getRadius()) - (balls[0]->x + balls[0]->radius)) +
            ((poolCue.getPosition().y + poolCue.getRadius()) - (balls[0]->y + balls[0]->radius)) * 
            ((poolCue.getPosition().y + poolCue.getRadius()) - (balls[0]->y + balls[0]->radius)));  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            float x1 = poolCue.getPosition().x - (balls[0]->x + (balls[0]->radius/2));
            float y1 = poolCue.getPosition().y - (balls[0]->y + (balls[0]->radius / 2));

            float x2 = x1 * cos(angle*dt) - y1 * sin(angle*dt);
            float y2 = x1 * sin(angle*dt) + y1 * cos(angle*dt);
            
            poolCue.setPosition(x2 + (balls[0]->x + (balls[0]->radius / 2)), y2 + (balls[0]->y + (balls[0]->radius / 2)));

            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            float x1 = poolCue.getPosition().x - (balls[0]->x + (balls[0]->radius/2));
            float y1 = poolCue.getPosition().y - (balls[0]->y + (balls[0]->radius / 2));
            float x2 = x1 * cos(-angle*dt) - y1 * sin(-angle*dt);
            float y2 = x1 * sin(-angle*dt) + y1 * cos(-angle*dt);
            

            poolCue.setPosition(x2 + (balls[0]->x + (balls[0]->radius / 2)), y2 + (balls[0]->y + (balls[0]->radius / 2)));

            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (distance <= 500) {
                poolCue.setPosition(PlayerManager::setPower(balls[0], poolCue.getPosition(), false));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (distance >= 40) {
                poolCue.setPosition(PlayerManager::setPower(balls[0], poolCue.getPosition(), true));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            moveBall(poolCue.getPosition().x-poolCue.getRadius(), poolCue.getPosition().y-poolCue.getRadius());
            return;
        }

        // cout << "test\n";
        window.clear();
        window.draw(innerTable);
        for(int i = 0; i < ballNumbers; i++){
            window.draw(*ballShapes[i]);
        }
        window.draw(line, 2, sf::Lines);
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
	innerTable.setPosition(210.f,210.f);
	innerTable.setFillColor(sf::Color::Green);
	innerTable.setOutlineThickness(59.f);
	innerTable.setOutlineColor(sf::Color::Blue);
    
    for(int i = 0; i < ballNumbers; i++){
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

    poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10));
    poolCue.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        playerTurn();
        poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10)); //set the pool cue.
        
        
        window.clear();
        window.draw(innerTable);
        for(int i = 0; i < ballNumbers; i++){
            window.draw(*ballShapes[i]);
        }
        window.display();
	}
    return 0;
}