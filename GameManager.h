#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "PlayerManager.h"
#include <SFML/Graphics.hpp>
enum gameState{PLAYERTURN, MOVEMENT};
extern gameState state;
extern sf::RectangleShape innerTable;
extern sf::RectangleShape cushions[];
extern sf::Vector2f cushionPositions[];
extern sf::CircleShape sockets[];
extern sf::Vector2f socketPositions[];
extern sf::Vertex socketEdges[18][2];
extern sf::Vector2f cornerPositions[12];
extern Ball* cornerObjects[12];
extern sf::CircleShape* cornerShapes[12];

class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
};
#endif