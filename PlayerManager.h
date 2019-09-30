#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include "Physics.h"
#include "Ball.h"
#include "MovementManager.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include <math.h>
extern sf::CircleShape poolCue;
extern sf::Vertex guideLine[];
extern bool endTurn;
extern bool screenSelected;
extern sf::Sprite cueSprite;
extern sf::Vector2f originalPower;
extern sf::RectangleShape powerBarBorder;
extern sf::RectangleShape powerBar;
class PlayerManager {
    public:
        static void playerTurn(Ball *whiteBall, sf::Event event, sf::RenderWindow& window);
        static void moveCue(Ball *whiteBall);
        static void placeWhiteBall(Ball *ball, sf::CircleShape *ballShape, Ball *balls[]);
        static void setPower(Ball *whiteBall, bool elevation);

    private:
        static void aim(Ball *whiteBall, bool direction);
        static void left(Ball *whiteBall);
        static void right(Ball *whiteBall);
        static void mouseAim(Ball *whiteBall, sf::Event event, float r);
        static sf::Vector2f guidelineVector(Ball *whiteBall, sf::CircleShape poolCue);
};
#endif