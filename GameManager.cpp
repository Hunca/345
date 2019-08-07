#include "GameManager.h"
#include <String>
#include <iostream>
sf::Vector2f initialPositions[] = { //array of the balls positions
    sf::Vector2f(600.5f, 381.f),  sf::Vector2f(701.5f,400.5f), sf::Vector2f(861.5f,360.5f),  sf::Vector2f(741.5f,420.5f), //0, 1, 2, 3
    sf::Vector2f(821.5f,420.5f),  sf::Vector2f(861.5f,440.5f), sf::Vector2f(781.5f,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
    sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f), sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
    sf::Vector2f(861.5f,480.5f),  sf::Vector2f(821.5f,340.5f), sf::Vector2f(781.5f,440.5f),  sf::Vector2f(821.5f,380.5f), //12, 13, 14, 15
};
void GameManager::tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers) {
    innerTable.setPosition(210.f, 210.f);
    innerTable.setFillColor(sf::Color::Green);
    innerTable.setOutlineThickness(59.f);
    innerTable.setOutlineColor(sf::Color::Yellow);
    for(int i = 0; i < 6; i++){
        cushions[i].setPosition(cushionPositions[i]);
        cushions[i].setFillColor(sf::Color::Blue);
        cushions[i].setOutlineThickness(0.f);
        cushions[i].setOutlineColor(sf::Color::Blue);
    }
    for (int i = 0; i < ballNumbers; i++) {
        balls[i] = new Ball(i, 20.f, initialPositions[i].x, initialPositions[i].y);
        ballShapes[i] = new sf::CircleShape(balls[i]->radius);
        ballShapes[i]->setPosition(balls[i]->x, balls[i]->y);
        if (balls[i]->num < 8) {
            ballShapes[i]->setFillColor(sf::Color::Blue);
        } else if (balls[i]->num > 8) {
            ballShapes[i]->setFillColor(sf::Color::Red);
        }
        if (balls[i]->num == 0) {
            ballShapes[i]->setFillColor(sf::Color::White);
        } if (balls[i]->num == 8) {
            ballShapes[i]->setFillColor(sf::Color::Black);
        }
    }
    player.ballSuit = 0;
    player.playerNum = 1;
    player.playersBallsLeft = 7;
    player.ballSunk = false;
    player.fouled = false;

    poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10));
    poolCue.setFillColor(sf::Color::Black);
}

void GameManager::ballSunk(Ball *ball) {
    if(ball->num == 0) {
        // player.fouled = true;
        // player.ballSunk = false;
    } else if(ball->num == 8) {
        
    } else if(!player.fouled) {
        if(ball->num < 8 && player.ballSuit == 1) {
            if(!ballSunk) player.ballSunk = true;
            player.playersBallsLeft--;
        } else if(ball->num > 8 && player.ballSuit == 9) {
            if(!ballSunk) player.ballSunk = true;
            player.playersBallsLeft--;
        }
        ball->isSunk = true;
        ball->x = -100;
        ball->y = -100;
        ballsLeft--;
    }
}

void GameManager::swapPlayer() {
    if(player.playerNum == 1){
        player.playerNum = 2;
        poolCue.setFillColor(sf::Color::Magenta);
    } else {
        player.playerNum = 1;
        poolCue.setFillColor(sf::Color::Black);
    }
    if(player.ballSuit == 1){
        player.ballSuit = 9;
    } else if(player.ballSuit == 9) {
        player.ballSuit = 1;
    }
    player.ballSunk = false;
    player.fouled = false;
    player.playersBallsLeft = ballsLeft - player.playersBallsLeft - 1;
    std::cout << "Player: " << player.playerNum << "\n";
    std::cout << "Suit: " << player.ballSuit << "\n";
    std::cout << "Balls left: " << player.playersBallsLeft << "\n";
}