#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "PlayerManager.h"
#include <SFML/Graphics.hpp>
enum gameState{PLAYERTURN, MOVEMENT};
extern gameState state;
extern sf::RectangleShape innerTable;
class GameManager {
    public:
        static void tableSetup(Ball *balls[], sf::CircleShape *ballShapes[], int ballNumbers);
};
#endif