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
extern Player *player1;
extern Player *player2;
extern sf::Vertex dLine[];
extern sf::RectangleShape cushions[];
extern sf::Vector2f cushionPositions[];
extern sf::CircleShape sockets[];
extern sf::Vector2f socketPositions[];
extern sf::Vertex socketEdges[18][2];
extern sf::Vector2f cornerPositions[12];
extern Ball* cornerObjects[12];
extern sf::CircleShape* cornerShapes[12];

extern int playerGoing;
class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
        static void ballSunk(Ball *ball);
        static void swapPlayer();
        static void lose();
        static void win();
};
#endif