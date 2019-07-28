#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "Physics.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <math.h>
extern sf::CircleShape poolCue;
extern sf::Vertex line[];
class PlayerManager {
    public:
        static sf::Vector2f setPower(Ball *whiteBall, sf::Vector2f pos, bool elevation);
};
#endif