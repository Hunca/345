#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "Physics.h"
#include "Ball.h"
#include "MovementManager.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include <math.h>
extern sf::CircleShape poolCue;
extern sf::Vertex line[];
extern bool endTurn;
extern bool screenSelected;
class PlayerManager {
    public:
        static void playerTurn(Ball *whiteBall, sf::Event event);

        static void placeWhiteBall(Ball *ball, sf::CircleShape *ballShape, Ball *balls[]);
        static void setPower(Ball *whiteBall, bool elevation);

    private:
        static void aim(Ball *whiteBall, bool direction);
        static void left(Ball *whiteBall);
        static void right(Ball *whiteBall);
        static void mouseAim(Ball *whiteBall, sf::Event event);
};
#endif