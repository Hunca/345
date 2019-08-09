#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Physics.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct player {
    int ballSuit;
    int playersBallsLeft;
    int player;
};
int ballNumbers = 16;
int ballsLeft = 15;
int windowWidth = 1182, windowHeight = 801;
int tableWidth = 762, tableHeight = 381;
bool noMovement = true; //boolean for moving balls
float cornerRadius = 8.55f; //Radius of the circles on each cushion corner
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "8BallPool");
sf::RectangleShape innerTable(sf::Vector2f(tableWidth, tableHeight));
sf::RectangleShape cushions[] = {sf::RectangleShape(sf::Vector2f(336.f, 44.25f)), sf::RectangleShape(sf::Vector2f(336.f, 44.25f)),  // Top 2
                                 sf::RectangleShape(sf::Vector2f(44.25f, 336.f)), sf::RectangleShape(sf::Vector2f(44.25f, 336.f)),  // Left and right
                                 sf::RectangleShape(sf::Vector2f(336.f, 44.25f)), sf::RectangleShape(sf::Vector2f(336.f, 44.25f))}; // Bottom 2
sf::Vector2f cushionPositions[] = {sf::Vector2f(235.f, 165.75f), sf::Vector2f(611.f, 165.75f), // Top 2
                                   sf::Vector2f(165.75f, 235.f), sf::Vector2f(972.f, 235.f),   // Left and right
                                   sf::Vector2f(235.f, 591.f), sf::Vector2f(611.f, 591.f)};    // Bottom 2
sf::CircleShape sockets[] = {sf::CircleShape(20.f), sf::CircleShape(20.f), sf::CircleShape(20.f),  // Top row
                             sf::CircleShape(20.f), sf::CircleShape(20.f), sf::CircleShape(20.f)}; // Bottomw row
sf::Vector2f socketPositions[] = {sf::Vector2f(174.9f, 174.9f), sf::Vector2f(571.f, 164.9f), sf::Vector2f(967.1f, 174.9f),  // Top row
                                  sf::Vector2f(174.9f, 587.1f), sf::Vector2f(571.f, 595.25f), sf::Vector2f(967.1f, 587.1f)}; // Bottom row
sf::Vertex socketEdges[18][2] = {{sf::Vertex(sf::Vector2f(210.f, 235.f), sf::Color::Black), sf::Vertex(sf::Vector2f(180.f, 205.f), sf::Color::Black)},   // TL Left
                                 {sf::Vertex(sf::Vector2f(235.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(205.f, 180.f), sf::Color::Black)},   // TL Right
                                 {sf::Vertex(sf::Vector2f(571.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(586.f, 180.f), sf::Color::Black)},   // TM Left
                                 {sf::Vertex(sf::Vector2f(611.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(596.f, 180.f), sf::Color::Black)},   // TM Right
                                 {sf::Vertex(sf::Vector2f(947.f, 210.f), sf::Color::Black), sf::Vertex(sf::Vector2f(977.f, 180.f), sf::Color::Black)},   // TR Left
                                 {sf::Vertex(sf::Vector2f(972.f, 235.f), sf::Color::Black), sf::Vertex(sf::Vector2f(1002.f, 205.f), sf::Color::Black)},   // TR Right
                                 {sf::Vertex(sf::Vector2f(210.f, 571.f), sf::Color::Black), sf::Vertex(sf::Vector2f(180.f, 601.f), sf::Color::Black)},   // BL Left
                                 {sf::Vertex(sf::Vector2f(235.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(205.f, 621.f), sf::Color::Black)},   // BL Right
                                 {sf::Vertex(sf::Vector2f(571.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(586.f, 621.f), sf::Color::Black)},   // BM Left
                                 {sf::Vertex(sf::Vector2f(611.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(596.f, 621.f), sf::Color::Black)},   // BM Right
                                 {sf::Vertex(sf::Vector2f(947.f, 591.f), sf::Color::Black), sf::Vertex(sf::Vector2f(977.f, 621.f), sf::Color::Black)},   // BR Left
                                 {sf::Vertex(sf::Vector2f(972.f, 571.f), sf::Color::Black), sf::Vertex(sf::Vector2f(1002.f, 601.f), sf::Color::Black)}, // BR Right
                                 {sf::Vertex(sf::Vector2f(235.f, 210.f)), sf::Vertex(sf::Vector2f(571.f, 210.f))},
                                 {sf::Vertex(sf::Vector2f(611.f, 210.f)), sf::Vertex(sf::Vector2f(947.f, 210.f))},
                                 {sf::Vertex(sf::Vector2f(210.f, 235.f)), sf::Vertex(sf::Vector2f(210.f, 571.f))},
                                 {sf::Vertex(sf::Vector2f(972.f, 235.f)), sf::Vertex(sf::Vector2f(972.f, 571.f))},
                                 {sf::Vertex(sf::Vector2f(235.f, 591.f)), sf::Vertex(sf::Vector2f(571.f, 591.f))},
                                 {sf::Vertex(sf::Vector2f(611.f, 591.f)), sf::Vertex(sf::Vector2f(947.f, 591.f))}
                                 };
float trig = (cornerRadius/tan(45));
sf::Vector2f cornerPositions[] = { //array of the balls positions
    sf::Vector2f(210.f-(2*cornerRadius), 235.f-trig), sf::Vector2f(235.f-trig, 210.f-(2*cornerRadius)), // top Left
    sf::Vector2f(571.f-(2*cornerRadius)+trig, 210.f-(2*cornerRadius)), sf::Vector2f(611.f-trig, 210.f-(2*cornerRadius)), // Top Middle
    sf::Vector2f(947.f-(2*cornerRadius)+trig, 210.f-(2*cornerRadius)),  sf::Vector2f(972.f, 235.f-trig), // Top Right
    sf::Vector2f(220.f ,360.5f),  sf::Vector2f(861.5f,320.5f), //4, 5, 6, 7
    sf::Vector2f(781.5f,400.5f),  sf::Vector2f(821.5f,460.5f),
    sf::Vector2f(861.5f,400.5f),  sf::Vector2f(741.5f,380.5f), //8, 9, 10, 11
};
Ball *cornerObjects[12];
Ball *balls[16];
sf::CircleShape* cornerShapes[12];
sf::CircleShape *ballShapes[16];
sf::CircleShape poolCue(10);
sf::Vertex line[2];
sf::Clock dtClock;
float dt;
bool endTurn = false;
gameState state = PLAYERTURN;
bool screenSelected = true;

void draw(gameState state) {
    window.clear();
    window.draw(innerTable);
    for(int i = 0; i < 6; i++){
        window.draw(sockets[i]);
        window.draw(cushions[i]);
    }
    for(int i = 0; i < ballNumbers; i++){
        //if(i < 12){
            window.draw(socketEdges[i], 2, sf::Lines);
        //}
        window.draw(*ballShapes[i]);
    }
    for(int i = 0; i < 12; i++){
        window.draw(*cornerShapes[i]);
    }
    if(state == PLAYERTURN) {
        window.draw(poolCue);
        window.draw(line, 2, sf::Lines);
    }
    window.display();
}
int main() {
    GameManager::tableSetup(balls, ballShapes, ballNumbers);
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
        if(event.type == sf::Event::GainedFocus) screenSelected = true;
        if(event.type == sf::Event::LostFocus) screenSelected = false;
        
        if(state == PLAYERTURN) {
            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(balls[0]->x + balls[0]->radius, balls[0]->y + balls[0]->radius), sf::Color::Black);
            PlayerManager::playerTurn(balls[0]);
        }
        if(state == MOVEMENT) {
            MovementManager::moveTick(balls, ballShapes, poolCue.getPosition().x, poolCue.getPosition().y);
        }
        draw(state);
	}
    return 0;
}
// void swapPlayer(player player){
//     if(player.player == 1){
//         player.player = 2;
//     }
//     if(player.ballSuit < 8){
//         player.ballSuit = 9;
//     }
//     player.playersBallsLeft = ballsLeft - player.playersBallsLeft - 1;
// }