#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "PlayerManager.h"
#include <SFML/Graphics.hpp>
enum gameState{PLAYERTURN, MOVEMENT};
extern gameState state;
extern sf::RectangleShape innerTable;
struct playerStruct {
    int ballSuit;
    int playersBallsLeft;
    int playerNum;
};
extern int ballsLeft;
extern playerStruct player;

class GameManager {
    public:
        static void swapPlayer();
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
};
#endif