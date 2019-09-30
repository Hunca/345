#include "PlayerManager.h"
#include <String>
#include <iostream>
float rad = 0;
sf::Vector2f PlayerManager::guidelineVector(Ball *whiteBall, sf::CircleShape poolCue){
    float x0 = whiteBall->x+whiteBall->radius, y0 = whiteBall->y+whiteBall->radius, x1 = poolCue.getPosition().x+poolCue.getRadius(), y1 = poolCue.getPosition().y+poolCue.getRadius();
    sf::Vector2f newPoint = sf::Vector2f(0.f, 0.f);
    if(x1==x0){
        if(y1>y0){
            newPoint = sf::Vector2f(x0, 210.f);
        } else {
            newPoint = sf::Vector2f(x0, 591.f);
        }
    } else if(y1==y0){
        if( x1>x0){
            newPoint = sf::Vector2f(210.f, y0);
        } else {
            newPoint = sf::Vector2f(974.f, y0);
        }
    } else {
        if(x1>x0){
            float yWithX = ((y1-y0)/(x1-x0))*(210-x0)+y0;
            if(210 <= yWithX && yWithX <= 591){
                newPoint = sf::Vector2f(210.f, yWithX);
            }
        } else if(x1<x0){
            float yWithX = ((y1-y0)/(x1-x0))*(974-x0)+y0;
            if(210 <= yWithX && yWithX <= 591){
                newPoint = sf::Vector2f(974.f, yWithX);
            }
        }
        if(y1>y0){
            float xWithY = ((x1-x0)/(y1-y0))*(210-y0)+x0;
            if(210 <= xWithY && xWithY <= 974){
                newPoint = sf::Vector2f(xWithY, 210.f);
            }
        } else if(y1<y0){
            float xWithY = ((x1-x0)/(y1-y0))*(591-y0)+x0;
            if(210 <= xWithY && xWithY <= 974){
                newPoint = sf::Vector2f(xWithY, 591.f);
            }
        }
    }
    return newPoint;
}
void PlayerManager::setPower(Ball *whiteBall, bool elevation) {
    float delta_x = poolCue.getPosition().x + poolCue.getRadius() - (whiteBall->x + whiteBall->radius);
    float delta_y = poolCue.getPosition().y + poolCue.getRadius() - (whiteBall->y + whiteBall->radius);
    float dist = sqrt((delta_x*delta_x)+(delta_y*delta_y));
    float xChange = (delta_x/dist)*(100*dt);
    float yChange = (delta_y/dist)*(100*dt);
    if(elevation) {
        poolCue.setPosition(poolCue.getPosition().x-xChange, poolCue.getPosition().y-yChange);
    } else {
        poolCue.setPosition(poolCue.getPosition().x + xChange, poolCue.getPosition().y + yChange);
    }
    rad = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)) *
        ((poolCue.getPosition().x + poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)) +
        ((poolCue.getPosition().y + poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)) * 
        ((poolCue.getPosition().y + poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)));
}
void PlayerManager::mouseAim(Ball *whiteBall, sf::Event event, float r) {
    if(event.type == sf::Event::MouseMoved){
        float R = r;
        float vX = (event.mouseMove.x - poolCue.getRadius()) - (whiteBall->x);
        float vY = (event.mouseMove.y - poolCue.getRadius()) - (whiteBall->y);
        float magV = sqrt(vX * vX + vY * vY);
        float aX = (whiteBall->x) + vX / magV * R;
        float aY = (whiteBall->y) + vY / magV * R;
        poolCue.setPosition(aX, aY);
        float cueAngleRad = atan2(((aY+poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)), ((aX+poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)));
        cueSprite.setRotation(cueAngleRad*(180/(atan(1)*4)) + 90);
    }
}
void PlayerManager::moveCue(Ball *whiteBall){
    dt = dtClock.restart().asSeconds();
    float delta_x = poolCue.getPosition().x + poolCue.getRadius() - (whiteBall->x + whiteBall->radius);
    float delta_y = poolCue.getPosition().y + poolCue.getRadius() - (whiteBall->y + whiteBall->radius);
    float dist = sqrt((delta_x*delta_x)+(delta_y*delta_y));
    float xChange = (delta_x/dist)*(1500*dt);
    float yChange = (delta_y/dist)*(1500*dt);
    poolCue.setPosition(poolCue.getPosition().x-xChange, poolCue.getPosition().y-yChange);
    if(dist <= whiteBall->radius){
        state = MOVEMENT;
    }
}
void PlayerManager::playerTurn(Ball *whiteBall, sf::Event event) {
    if(screenSelected == false) return;
    guideLine[0] = sf::Vertex(sf::Vector2f(whiteBall->x+whiteBall->radius, whiteBall->y+whiteBall->radius), sf::Color::White);
    guideLine[1] = sf::Vertex(sf::Vector2f(guidelineVector(whiteBall, poolCue)), sf::Color::White);
    dt = dtClock.restart().asSeconds();
    float distance = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)) *
        ((poolCue.getPosition().x + poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)) +
        ((poolCue.getPosition().y + poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)) * 
        ((poolCue.getPosition().y + poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(rad == 0) rad = whiteBall->radius + poolCue.getRadius();
        mouseAim(whiteBall, event, rad);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (distance <= 200) { //alter distance of cue
            setPower(whiteBall, false);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (distance >= whiteBall->radius + 1) {
            setPower(whiteBall, true);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        originalPower = poolCue.getPosition();
        state = MOVECUE;
        rad = whiteBall->radius + poolCue.getRadius();
    }
}
void PlayerManager::placeWhiteBall(Ball *ball, sf::CircleShape *ballShape, Ball *balls[]) {
    float speed = 100;
    dt = dtClock.restart().asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if(ball->x + (ball->radius*2) < 210+tableWidth && state == WHITEPLACEMENT) {
            ball->x += speed * dt;
            ballShape->setPosition(ball->x, ball->y);
        } else if(ball->x + (ball->radius*2) < (400.5+ball->radius) && state == BREAKING){
            ball->x += speed * dt;
            ballShape->setPosition(ball->x, ball->y);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(ball->x > 210) {
            ball->x -= speed*dt;
            ballShape->setPosition(ball->x, ball->y);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
       if(ball->y > 210.f) {
            ball->y -= speed*dt;
            ballShape->setPosition(ball->x, ball->y);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if(ball->y + (ball->radius*2) < 210+tableHeight) {
            ball->y += speed * dt;
            ballShape->setPosition(ball->x, ball->y);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bool overlapCheck = false;
        for (int i = 1; i < ballNumbers; i++) {
            if(Physics::overLapDetection(ball, balls[i])) {
                overlapCheck = true;
            }
        }
        if(overlapCheck == false) {
            poolCue.setPosition(sf::Vector2f(ball->x, ball->y - poolCue.getRadius()));
            ball->isSunk = false;
            state = PLAYERTURN;
        }
    }
}