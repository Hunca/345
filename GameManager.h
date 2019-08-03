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
    bool ballSunk;
    bool fouled;
};
extern int ballsLeft;
extern playerStruct player;

extern sf::RectangleShape cushions[];
extern sf::Vector2f cushionPositions[];
class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
        static void ballSunk(Ball ball);
        static void swapPlayer();
};
#endif