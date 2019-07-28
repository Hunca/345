#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "Physics.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <math.h>
extern sf::CircleShape poolCue;
extern sf::Vertex line[];
extern bool yeeted;
class PlayerManager {
    public:
        static void playerTurn(Ball *whiteBall);

        static void setPower(Ball *whiteBall, bool elevation);

    private:
        static void aim(Ball *whiteBall, bool direction);
        static void left(Ball *whiteBall);
        static void right(Ball *whiteBall);
};
#endif