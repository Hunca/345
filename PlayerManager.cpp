#include "PlayerManager.h"

sf::Vector2f PlayerManager::setPower(Ball *whiteBall, sf::Vector2f pos, bool elevation) {
    float delta_x = pos.x + poolCue.getRadius() - (whiteBall->x + whiteBall->radius);
    float delta_y = pos.y + poolCue.getRadius() - (whiteBall->y + whiteBall->radius);
    line[0] = sf::Vertex(sf::Vector2f(pos.x + poolCue.getRadius(), pos.y + poolCue.getRadius()), sf::Color::Black);
    line[1] = sf::Vertex(sf::Vector2f(whiteBall->x + whiteBall->radius, whiteBall->y + whiteBall->radius), sf::Color::Black);
    float dist = sqrt((delta_x*delta_x)+(delta_y*delta_y));
    float xChange = (delta_x/dist)*(100*dt);
    float yChange = (delta_y/dist)*(100*dt);
    if(elevation) {
        pos.x -=xChange;
        pos.y -=yChange;
    } else {
        pos.x +=xChange;
        pos.y +=yChange;
    }
    return pos;
}