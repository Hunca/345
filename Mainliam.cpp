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
sf::Vertex dLine[2];
sf::Clock dtClock;
sf::Sprite cueSprite;
sf::Vector2f originalPower;
float dt;
bool endTurn = false;
gameState state = MENU;
bool screenSelected = true;

sf::RectangleShape playButton(sf::Vector2f(160, 40));
sf::Text playButtonText("Play", font);

sf::RectangleShape exitButton(sf::Vector2f(160, 40));
sf::Text exitButtonText("Exit", font);
void draw() {
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
    if(state != MENU && state != END) {
        for(int i = 0; i < ballNumbers; i++) {
            if(balls[i]->isSunk == false) {
                sf::Texture ballTexture;
                string fileName = "sprites/" + to_string(i);
                ballTexture.loadFromFile(fileName + "_ball.png");
                ballTexture.setSmooth(true);
                sf::Sprite ballSprite;
                ballSprite.setTexture(ballTexture);
                ballSprite.setPosition(ballShapes[i]->getPosition());
                window.draw(ballSprite);
            }
        }
    }
    if(balls[0]->isSunk == false && (state != MENU && state != END)) window.draw(*ballShapes[0]);
    
    if(state == PLAYERTURN || state == MOVECUE) {
        sf::Texture cueTexture;
        cueTexture.loadFromFile("sprites/1_cue.png");
        cueTexture.setSmooth(true);
        cueSprite.setTexture(cueTexture);
        cueSprite.setOrigin(sf::Vector2f(7,291));
        cueSprite.setPosition(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius());
        window.draw(guideLine, 2, sf::Lines);
        window.draw(cueSprite);
    }
    if(players[playerGoing]->ballSuit == 1) {
        suitText.setString("Suit: Solids");
    } else if (players[playerGoing]->ballSuit == 9) {
        suitText.setString("Suit: Stripes");
    }
    playerText.setString("Player " + std::to_string(players[playerGoing]->playerNum+1));
    if(players[playerGoing]->playersBallsLeft != 0) {
        remainingText.setString("Remaining: " + std::to_string(players[playerGoing]->playersBallsLeft));
    } else {
        remainingText.setString("Remaining: Black");
    }
    if(state != MENU && state != END)  {
        window.draw(playerText);
        window.draw(remainingText);
        window.draw(suitText);
    }
    if (state == BREAKING || state == WHITEPLACEMENT) window.draw(controlPrompText);
    if(state == MENU) {
        playButton.setPosition(511, 300);
        playButtonText.setPosition(561, 300);
        playButtonText.setFillColor(sf::Color::Black);
        exitButton.setPosition(511, 400);
        exitButtonText.setFillColor(sf::Color::Black);
        exitButtonText.setPosition(561, 400);
        window.draw(playButton);
        window.draw(playButtonText);
        window.draw(exitButton);
        window.draw(exitButtonText);
    }
    if(state == END) {

        endGameText.setPosition(561, 300);
        endGameText.setFillColor(sf::Color::Black);
        window.draw(endGameText);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && state != MOVEMENT && state != MENU) {//reset
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
            MovementManager::moveTick(balls, ballShapes, originalPower.x, originalPower.y);
        }
        if(state == MOVECUE){
            PlayerManager::moveCue(balls[0]);
        }
        if(state == MENU) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            if((pos.x > 511 && pos.x < 511+160) && (pos.y > 300 && pos.y < 300 + 40)) {
                playButton.setOutlineColor(sf::Color::Black);
                playButton.setOutlineThickness(1);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    state = BREAKING;
                }
            }else {
                playButton.setOutlineThickness(0);
            }

            if((pos.x > 511 && pos.x < 511+160) && (pos.y > 400 && pos.y < 400 + 40)) {
                exitButton.setOutlineColor(sf::Color::Black);
                exitButton.setOutlineThickness(1);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    window.close();
                    return 0;
                }
            }else {
                exitButton.setOutlineThickness(0);
            } 
        }
        draw();
	}
    return 0;
}
