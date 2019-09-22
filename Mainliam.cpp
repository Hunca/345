#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Physics.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int movingBalls = 0;
int ballNumbers = 16;
int ballsLeft = 15;
int windowWidth = 1182, windowHeight = 801;
int tableWidth = 762, tableHeight = 381;
bool noMovement = true; //boolean for moving balls
float cornerRadius = 8.55f; //Radius of the circles on each cushion corner
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "8BallPool");
sf::RectangleShape innerTable(sf::Vector2f(tableWidth, tableHeight));
sf::RectangleShape cushions[] = {sf::RectangleShape(sf::Vector2f(336.f, 44.25f)), sf::RectangleShape(sf::Vector2f(336.f, 44.25f)),  // Top 2
                                 sf::RectangleShape(sf::Vector2f(44.25f, 336.f)), sf::RectangleShape(sf::Vector2f(44.25f, 336.f)),  // Left and right
                                 sf::RectangleShape(sf::Vector2f(336.f, 44.25f)), sf::RectangleShape(sf::Vector2f(336.f, 44.25f))}; // Bottom 2
sf::Vector2f cushionPositions[] = {sf::Vector2f(235.f, 165.75f), sf::Vector2f(611.f, 165.75f), // Top 2
                                   sf::Vector2f(165.75f, 235.f), sf::Vector2f(972.f, 235.f),   // Left and right
                                   sf::Vector2f(235.f, 591.f), sf::Vector2f(611.f, 591.f)};    // Bottom 2
sf::CircleShape sockets[] = {sf::CircleShape(20.f), sf::CircleShape(20.f), sf::CircleShape(20.f),  // Top row
                             sf::CircleShape(20.f), sf::CircleShape(20.f), sf::CircleShape(20.f)}; // Bottomw row
sf::Vector2f socketPositions[] = {sf::Vector2f(174.9f, 174.9f), sf::Vector2f(571.f, 164.9f), sf::Vector2f(967.1f, 174.9f),  // Top row
                                  sf::Vector2f(174.9f, 587.1f), sf::Vector2f(571.f, 595.25f), sf::Vector2f(967.1f, 587.1f)}; // Bottom row
sf::Vertex socketEdges[24][2] = {{sf::Vertex(sf::Vector2f(210.f, 235.f), sf::Color::Black), sf::Vertex(sf::Vector2f(180.f, 205.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(235.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(205.f, 180.f), sf::Color::Black)},   // TL Right
                                 {sf::Vertex(sf::Vector2f(571.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(586.f, 180.f), sf::Color::Black)},   // TM Left
                                 {sf::Vertex(sf::Vector2f(611.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(596.f, 180.f), sf::Color::Black)},   // TM Right
                                 {sf::Vertex(sf::Vector2f(947.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(977.f, 180.f), sf::Color::Black)},   // TR Left
                                 {sf::Vertex(sf::Vector2f(972.f, 235.f), sf::Color::Black), sf::Vertex(sf::Vector2f(1002.f, 205.f), sf::Color::Black)},   // TR Right
                                 {sf::Vertex(sf::Vector2f(210.f, 571.f), sf::Color::Black), sf::Vertex(sf::Vector2f(180.f, 601.f), sf::Color::Black)},   // BL Left
                                 {sf::Vertex(sf::Vector2f(235.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(205.f, 621.f), sf::Color::Black)},   // BL Right
                                 {sf::Vertex(sf::Vector2f(571.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(586.f, 621.f), sf::Color::Black)},   // BM Left
                                 {sf::Vertex(sf::Vector2f(611.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(596.f, 621.f), sf::Color::Black)},   // BM Right
                                 {sf::Vertex(sf::Vector2f(947.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(977.f, 621.f), sf::Color::Black)},   // BR Left
                                 {sf::Vertex(sf::Vector2f(972.f, 571.f), sf::Color::Black), sf::Vertex(sf::Vector2f(1002.f, 601.f), sf::Color::Black)}, // BR Right
                                 {sf::Vertex(sf::Vector2f(235.f, 210.f)), sf::Vertex(sf::Vector2f(571.f, 210.f))}, // Top Left
                                 {sf::Vertex(sf::Vector2f(611.f, 210.f)), sf::Vertex(sf::Vector2f(947.f, 210.f))}, // Top Right
                                 {sf::Vertex(sf::Vector2f(210.f, 235.f)), sf::Vertex(sf::Vector2f(210.f, 571.f))}, // Left
                                 {sf::Vertex(sf::Vector2f(972.f, 235.f)), sf::Vertex(sf::Vector2f(972.f, 571.f))}, // Right
                                 {sf::Vertex(sf::Vector2f(235.f, 591.f)), sf::Vertex(sf::Vector2f(571.f, 591.f))}, // Bottom Left
                                 {sf::Vertex(sf::Vector2f(611.f, 591.f)), sf::Vertex(sf::Vector2f(947.f, 591.f))}, // Bottom Right
                                 {sf::Vertex(sf::Vector2f(180.f, 205.f), sf::Color::Black), sf::Vertex(sf::Vector2f(205.f, 180.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(586.f, 180.f), sf::Color::Black), sf::Vertex(sf::Vector2f(596.f, 180.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(977.f, 180.f), sf::Color::Black), sf::Vertex(sf::Vector2f(1002.f, 205.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(180.f, 601.f), sf::Color::Black), sf::Vertex(sf::Vector2f(205.f, 621.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(586.f, 621.f), sf::Color::Black), sf::Vertex(sf::Vector2f(596.f, 621.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(977.f, 621.f), sf::Color::Black), sf::Vertex(sf::Vector2f(1002.f, 601.f), sf::Color::Black)}};   // TL Left
sf::Vertex guideLine[2];
Ball *balls[16];
bool placing = false;
sf::CircleShape *ballShapes[16];
sf::CircleShape poolCue(8.55f);
sf::Vertex line[2];
sf::Vertex dLine[2];
sf::Clock dtClock;
float dt;
bool endTurn = false;
gameState state = BREAKING;
bool screenSelected = true;
void draw(gameState state) {
    window.clear();
    window.draw(innerTable);
    window.draw(dLine, 2, sf::Lines);
    for(int i = 0; i < 6; i++){
        window.draw(sockets[i]);
        window.draw(cushions[i]);
    }
    for(int i = 0; i < 18; i++){
        window.draw(socketEdges[i], 2, sf::Lines);
    }
    for(int i = 1; i < ballNumbers; i++) {
        if(balls[i]->isSunk == false) window.draw(*ballShapes[i]);
    }
    if(balls[0]->isSunk == false) window.draw(*ballShapes[0]);
    if(state == PLAYERTURN) {
        window.draw(guideLine, 2, sf::Lines);
        window.draw(poolCue);
        window.draw(line, 2, sf::Lines);
    }
    if(players[playerGoing]->ballSuit == 1) {
        suitText.setString("Suit: blue");
    } else if (players[playerGoing]->ballSuit == 9) {
        suitText.setString("Suit: red");
    }
    playerText.setString("Player " + std::to_string(players[playerGoing]->playerNum+1));
    if(players[playerGoing]->playersBallsLeft != 0) {
        remainingText.setString("Remaining: " + std::to_string(players[playerGoing]->playersBallsLeft));
    } else {
        remainingText.setString("Remaining: Black");
    }
    window.draw(playerText);
    window.draw(remainingText);
    window.draw(suitText);
    if (state == BREAKING || state == WHITEPLACEMENT) window.draw(controlPrompText);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && state != MOVEMENT) {//reset
            GameManager::tableSetup(balls, ballShapes, ballNumbers);
            ballsLeft = 15;
            playerGoing = 0;
            state = BREAKING;
        }
        if(event.type == sf::Event::KeyReleased) {
            if(event.key.code == sf::Keyboard::Space) {
                placing = false;
            }
        }

        if(placing == false && state == PLAYERTURN) {
            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
            PlayerManager::playerTurn(balls[0], event);
        }
        if(state == WHITEPLACEMENT) {
            placing = true;
            PlayerManager::placeWhiteBall(balls[0], ballShapes[0], balls);
        }
        if(state == BREAKING) {
            placing = true;
            PlayerManager::placeWhiteBall(balls[0], ballShapes[0], balls);
        }
        if(state == MOVEMENT) {
            MovementManager::moveTick(balls, ballShapes, poolCue.getPosition().x, poolCue.getPosition().y);
        }
        draw(state);
	}
    return 0;
}
