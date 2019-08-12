#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "Player.h"
#include "PlayerManager.h"
#include <SFML/Graphics.hpp>
enum gameState{PLAYERTURN, MOVEMENT, WHITEPLACEMENT, BREAKING};
extern gameState state;
extern sf::RectangleShape innerTable;
extern int ballsLeft;
extern sf::Vertex dLine[];
extern sf::RectangleShape cushions[];
extern sf::Vector2f cushionPositions[];
extern int playerGoing;
extern sf::Text playerText;
extern sf::Text suitText;
extern sf::Text remainingText;
extern sf::Text controlPrompText;
extern Player *players[];
class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
        static void ballSunk(Ball *ball);
        static void swapPlayer();
        static void lose();
        static void win();
};
#endif