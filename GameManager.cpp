#include "GameManager.h"
#include <String>
#include <iostream>
sf::Vector2f initialPositions[] = { //array of the balls positions
    sf::Vector2f(391.95f, 391.95f),  sf::Vector2f(741.83f,391.95f), sf::Vector2f(804.07f,373.85f),  sf::Vector2f(757.64f,400.5), //0, 1, 2, 3
    sf::Vector2f(788.26f,400.5f),  sf::Vector2f(804.07f,410.05f), sf::Vector2f(772.95f,373.85f),  sf::Vector2f(804.07f,355.75f), //4, 5, 6, 7
    sf::Vector2f(772.95f,391.95f),  sf::Vector2f(788.26f,418.6f), sf::Vector2f(804.07f,391.95f),  sf::Vector2f(757.64f,383.4f), //8, 9, 10, 11
    sf::Vector2f(804.07f,428.15f),  sf::Vector2f(788.26f,365.3f), sf::Vector2f(772.95f,410.05f),  sf::Vector2f(788.26f,383.4f), //12, 13, 14, 15
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
        balls[i] = new Ball(i, 8.55f, initialPositions[i].x, initialPositions[i].y);
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

    poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10));
    poolCue.setFillColor(sf::Color::Black);
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
    player.playersBallsLeft = ballsLeft - player.playersBallsLeft - 1;
    std::cout << "Player: " << player.playerNum << "\n";
    std::cout << "Suit: " << player.ballSuit << "\n";
    std::cout << "Balls left: " << player.playersBallsLeft << "\n";
}