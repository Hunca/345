#include "GameManager.h"
#include <String>
#include <iostream>
sf::Vector2f initialPositions[] = {
    //array of the balls positions
    sf::Vector2f(391.95f, 391.95f), sf::Vector2f(741.83f, 391.95f), sf::Vector2f(804.07f, 373.85f), sf::Vector2f(757.64f, 400.5),  //0, 1, 2, 3
    sf::Vector2f(788.26f, 400.5f), sf::Vector2f(804.07f, 410.05f), sf::Vector2f(772.95f, 373.85f), sf::Vector2f(804.07f, 355.75f), //4, 5, 6, 7
    sf::Vector2f(772.95f, 391.95f), sf::Vector2f(788.26f, 418.6f), sf::Vector2f(804.07f, 391.95f), sf::Vector2f(757.64f, 383.4f),  //8, 9, 10, 11
    sf::Vector2f(804.07f, 428.15f), sf::Vector2f(788.26f, 365.3f), sf::Vector2f(772.95f, 410.05f), sf::Vector2f(788.26f, 383.4f),  //12, 13, 14, 15
};
sf::Font font;
sf::Text playerText("Player1", font);
sf::Text remainingText("Remaining: 7", font);
sf::Text suitText("Suit: ", font);
sf::Text controlPrompText("Use the arrow keys to move the white ball and space to place it!", font);
sf::Text endGameText("", font);

int playerGoing = 0;
Player *players[2];
bool sunkBall = false;
bool foulSunk = false;
int winner = -1;
void GameManager::tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers) {
    winner = -1;
    dLine[0] = sf::Vertex(sf::Vector2f(400.5f, 210.f), sf::Color::Black);
    dLine[1] = sf::Vertex(sf::Vector2f(400.5f, 211.f+tableHeight), sf::Color::Black);
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
    
    players[0] = new Player(0);
    players[1] = new Player(1);
    font.loadFromFile("arial.ttf");
    playerText.setString("Player1");
    playerText.setCharacterSize(20);
    playerText.setStyle(sf::Text::Bold);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(10.f, 10.f);

    remainingText.setString("Remaining: 7");
    remainingText.setCharacterSize(20);
    remainingText.setStyle(sf::Text::Bold);
    remainingText.setFillColor(sf::Color::White);
    remainingText.setPosition(10.f, 50.f);

    controlPrompText.setCharacterSize(20);
    controlPrompText.setStyle(sf::Text::Bold);
    controlPrompText.setFillColor(sf::Color::Red);
    controlPrompText.setPosition(280.f, 100.f);
    
    suitText.setCharacterSize(20);
    suitText.setStyle(sf::Text::Bold);
    suitText.setFillColor(sf::Color::White);
    suitText.setPosition(10.f, 30.f);
    suitText.setString("Suit: none");
    poolCue.setPosition(sf::Vector2f(balls[0]->x, balls[0]->y - poolCue.getRadius()));
    poolCue.setFillColor(sf::Color::Black);
}
void GameManager::end(int endState) {
    if(winner == -1) {
        winner = endState;
    } else if(winner == 1) {
        winner = endState;
    }
}
void GameManager::ballSunk(Ball *ball) {
    if(ball->num == 0) {
        if(players[playerGoing]->playersBallsLeft == 0) {
            end(0);
        }
        ball->isSunk = true;
        foulSunk = true;
    } else if(ball->num == 8) {
        ball->isSunk = true;
        if(players[playerGoing]->playersBallsLeft == 0) {
            if(playerGoing == 0) {
                end(1);
            } 
        } else {
            end(0);
        }
    } else {
        if(players[playerGoing]->ballSuit == 0) {
            if(ball->num > 8) {
                players[playerGoing]->ballSuit = 9;
                if(playerGoing == 0) {
                    players[1]->ballSuit = 1;
                } else {
                    players[0]->ballSuit = 1;
                    sunkBall = true;
                }
            }
            else {
                players[playerGoing]->ballSuit = 1;
                if(playerGoing == 0) {
                    players[1]->ballSuit = 9;
                } else {
                    players[0]->ballSuit = 9;
                    sunkBall = true;
                }
            }
        }
        if(ball->num < 8) {
            if(players[playerGoing]->ballSuit == 1) {
                if(!ballSunk) players[playerGoing]->ballSunk = true;
                players[playerGoing]->playersBallsLeft--;
                sunkBall = true;
            } else {
                if(playerGoing == 0) {
                    players[1]->playersBallsLeft--;
                } else {
                    players[0]->playersBallsLeft--;
                }
                foulSunk = true;
            }
        } else if(ball->num > 8) {
            if(players[playerGoing]->ballSuit == 9) {
                if(!ballSunk) players[playerGoing]->ballSunk = true;
                players[playerGoing]->playersBallsLeft--;
                sunkBall = true;
            } else {
                if(playerGoing == 0) {
                    players[1]->playersBallsLeft--;
                } else {
                    players[0]->playersBallsLeft--;
                }
                foulSunk = true;
            }
        }
        ball->isSunk = true;
        ballsLeft--;
    }
}

void GameManager::swapPlayer() {
    if(winner != -1) {
        if(winner == 0) {
            if (playerGoing == 0) {
                endGameText.setString("Player: 2 Wins!");
            } else {
                endGameText.setString("Player: 1 Wins!");
            }
        } else if(winner == 1) {
            if (playerGoing == 0) {
                endGameText.setString("Player: 1 Wins!");
            } else {
                endGameText.setString("Player: 2 Wins!");
            }
        }
        state = END;
        return;
    }
    
    if(sunkBall && foulSunk == false && players[playerGoing]->fouled == false) {
        sunkBall = false;
        return;
    }
    if(players[playerGoing]->fouled) state = WHITEPLACEMENT;
    foulSunk = false;
    players[playerGoing]->fouled = false;
    if(playerGoing == 0){
        playerGoing = 1;
        poolCue.setFillColor(sf::Color::Magenta);
    } else {
        playerGoing = 0;
        poolCue.setFillColor(sf::Color::Black);
    }
}