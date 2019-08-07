#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "Player.h"
#include "PlayerManager.h"
#include <SFML/Graphics.hpp>
enum gameState{PLAYERTURN, MOVEMENT, WHITEPLACEMENT};
extern gameState state;
extern sf::RectangleShape innerTable;
extern int ballsLeft;
extern Player *player1;
extern Player *player2;
extern sf::RectangleShape cushions[];
extern sf::Vector2f cushionPositions[];
class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
        static void ballSunk(Ball *ball);
        static void swapPlayer();
};
#endif