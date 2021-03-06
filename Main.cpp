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
sf::CircleShape sockets[] = {sf::CircleShape(20.f), sf::CircleShape(20.f), sf::CircleShape(20.f),  // Top row
                             sf::CircleShape(20.f), sf::CircleShape(20.f), sf::CircleShape(20.f)}; // Bottom row
sf::Vector2f socketPositions[] = {sf::Vector2f(174.9f, 174.9f), sf::Vector2f(571.f, 164.9f), sf::Vector2f(967.1f, 174.9f),  // Top row
                                  sf::Vector2f(174.9f, 587.1f), sf::Vector2f(571.f, 595.25f), sf::Vector2f(967.1f, 587.1f)}; // Bottom row
sf::Vertex socketEdges[18][2] = {{sf::Vertex(sf::Vector2f(210.f, 235.f), sf::Color::Black), sf::Vertex(sf::Vector2f(180.f, 205.f), sf::Color::Black)},   // TL Left
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
                                 {sf::Vertex(sf::Vector2f(611.f, 591.f)), sf::Vertex(sf::Vector2f(947.f, 591.f))}};// Bottom Right
sf::Vertex guideLine[2];
Ball *balls[16];
bool placing = false;
sf::CircleShape *ballShapes[16];
sf::CircleShape poolCue(8.55f);
sf::Vertex dLine[2];
sf::Clock dtClock;
sf::Vector2f originalPower;
sf::RectangleShape powerBar;
sf::RectangleShape powerBarBorder(sf::Vector2f(50, 400));
float dt;
bool endTurn = false;
gameState state = MENU;
bool screenSelected = true;
sf::Sprite cueSprite, ballSprites[16], tableSprite, powerBarSprite;
sf::Texture tableTexture, ballTexture[16], cueTexture, powerBarTexture;
void loadSprites(){
    tableTexture.loadFromFile("sprites/table.png");
    for(int i = 0; i < ballNumbers; i++) {
        string fileName = "sprites/" + to_string(i);
        ballTexture[i].loadFromFile(fileName + "_ball.png");
        ballTexture[i].setSmooth(true);
    }
    cueTexture.loadFromFile("sprites/1_cue.png");
    powerBarTexture.loadFromFile("sprites/power_bar.png");
}

void draw() {
    window.clear();
    tableTexture.setSmooth(true);
    tableSprite.setTexture(tableTexture);
    tableSprite.setOrigin(56,56);
    tableSprite.setPosition(210,210);
    window.draw(tableSprite);
    

    if(state != MENU && state != END) {
        for(int i = 0; i < ballNumbers; i++) {
            if(balls[i]->isSunk == false) {
                sf::Sprite ballSprite;
                ballSprite.setTexture(ballTexture[i]);
                ballSprite.setPosition(ballShapes[i]->getPosition());
                ballSprites[i] = ballSprite;
                window.draw(ballSprites[i]);
            }
        }
    }  
    if(state == PLAYERTURN || state == MOVECUE) {
        cueTexture.setSmooth(true);
        cueSprite.setTexture(cueTexture);
        cueSprite.setOrigin(sf::Vector2f(7,291));
        cueSprite.setPosition(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius());
        powerBarTexture.setSmooth(true);
        powerBarSprite.setTexture(powerBarTexture);
        powerBarSprite.setPosition(20, 200);
        powerBarBorder.setPosition(20, 200);
        powerBar.setRotation(180);
        powerBar.setPosition(sf::Vector2f(powerBarBorder.getPosition().x + powerBarBorder.getSize().x - 12, powerBarBorder.getPosition().y + 400));
        powerBar.setFillColor(sf::Color::Red);
        window.draw(powerBarBorder);
        window.draw(powerBar);
        window.draw(powerBarSprite);
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
        sf::Texture exitTexture, playTexute;
        sf::Sprite exitSprite, playSprite;
        exitTexture.loadFromFile("sprites/exit_button.png");
        playTexute.loadFromFile("sprites/play_button.png");
        exitSprite.setTexture(exitTexture);
        playSprite.setTexture(playTexute);
        exitSprite.setPosition(511, 400);
        playSprite.setPosition(511, 300);
        window.draw(playSprite);
        window.draw(exitSprite);
    }
    if(state == END) {
        sf::Texture menuTexture;
        sf::Sprite menuSprite;
        menuTexture.loadFromFile("sprites/menu_button.png");
        menuTexture.setSmooth(true);
        menuSprite.setTexture(menuTexture);
        menuSprite.setPosition(511, 360);
        endGameText.setPosition(500, 300);
        window.draw(menuSprite);
        window.draw(endGameText);
    }
    window.display();
}
int main() {
    GameManager::tableSetup(balls, ballShapes, ballNumbers);
    loadSprites();
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && state != MOVEMENT && state != MENU) {//reset
            cueTexture.loadFromFile("sprites/1_cue.png");
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
            PlayerManager::playerTurn(balls[0], event, window);
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
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    state = BREAKING;
                }
            }
            if((pos.x > 511 && pos.x < 511+160) && (pos.y > 400 && pos.y < 400 + 40)) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    window.close();
                    return 0;
                }
            }
        }
        if(state == END) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            if((pos.x > 511 && pos.x < 511+160) && (pos.y > 360 && pos.y < 360 + 40)) {cueTexture.loadFromFile("sprites/1_cue.png");
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    GameManager::tableSetup(balls, ballShapes, ballNumbers);
                    ballsLeft = 15;
                    playerGoing = 0;
                    state = MENU;
                }
                    
            }
        }
        draw();
	}
    return 0;
}
