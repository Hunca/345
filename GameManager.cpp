#include "GameManager.h"
sf::Vector2f initialPositions[] = { //array of the balls positions
    sf::Vector2f(600.5f, 381.f),  sf::Vector2f(701.5f,400.5f), sf::Vector2f(861.5f,360.5f),  sf::Vector2f(741.5f,420.5f), //0, 1, 2, 3
    sf::Vector2f(821.5f,420.5f),  sf::Vector2f(861.5f,440.5f), sf::Vector2f(781.5f,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
    sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f), sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
    sf::Vector2f(861.5f,480.5f),  sf::Vector2f(821.5f,340.5f), sf::Vector2f(781.5f,440.5f),  sf::Vector2f(821.5f,380.5f), //12, 13, 14, 15
};

void GameManager::tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers) {
    innerTable.setPosition(210.f, 210.f);
    innerTable.setFillColor(sf::Color::Green);
    innerTable.setOutlineThickness(44.25f);
    innerTable.setOutlineColor(sf::Color::Yellow);
    for(int i = 0; i < 6; i++){
        sockets[i].setPosition(socketPositions[i]);
        sockets[i].setFillColor(sf::Color::Black);
        cushions[i].setPosition(cushionPositions[i]);
        cushions[i].setFillColor(sf::Color::Blue);
        cushions[i].setOutlineThickness(0.f);
        cushions[i].setOutlineColor(sf::Color::Blue);
    }
    for(int i = 0; i < 12; i++){
        cornerObjects[i] = new Ball(i, 8.55f, cornerPositions[i].x, cornerPositions[i].y);
        cornerShapes[i] = new sf::CircleShape(cornerObjects[i]->radius);
        cornerShapes[i]->setPosition(cornerPositions[i].x, cornerPositions[i].y);
        cornerShapes[i]->setFillColor(sf::Color::Black);
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
    poolCue.setPosition(sf::Vector2f(balls[0]->x + balls[0]->radius - 10, balls[0]->y - balls[0]->radius - 10));
    poolCue.setFillColor(sf::Color::Black);
}