#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "Player.h"
#include "PlayerManager.h"
#include <SFML/Graphics.hpp>
enum gameState{PLAYERTURN, MOVEMENT, WHITEPLACEMENT, BREAKING, MENU, MOVECUE, END};
extern gameState state;
extern sf::RectangleShape innerTable;
extern int ballsLeft;
extern sf::Font font;
extern sf::Vertex dLine[];
extern sf::CircleShape sockets[];
extern sf::Vector2f socketPositions[];
extern sf::Vertex socketEdges[24][2];
extern sf::Texture cueTexture;

extern int playerGoing;
extern sf::Text playerText;
extern sf::Text suitText;
extern sf::Text remainingText;
extern sf::Text controlPrompText;
extern sf::Text endGameText;

extern Player *players[];
class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
        static void ballSunk(Ball *ball);
        static void swapPlayer();
        static void end(int loser);
};
#endif