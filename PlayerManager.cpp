#include "PlayerManager.h"
#include <String>
#include <iostream>
float rad = 0;
void PlayerManager::setPower(Ball *whiteBall, bool elevation) {
    float delta_x = poolCue.getPosition().x + poolCue.getRadius() - (whiteBall->x + whiteBall->radius);
    float delta_y = poolCue.getPosition().y + poolCue.getRadius() - (whiteBall->y + whiteBall->radius);
    line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
    line[1] = sf::Vertex(sf::Vector2f(whiteBall->x + whiteBall->radius, whiteBall->y + whiteBall->radius), sf::Color::Black);
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
        guideLine[0] = sf::Vertex(sf::Vector2f(whiteBall->x, whiteBall->y));
        guideLine[1] = sf::Vertex(sf::Vector2f(guideLineVector(whiteBall, poolCue.getPosition())), sf::Color::Black);
    }
}
void PlayerManager::playerTurn(Ball *whiteBall, sf::Event event) {
    if(screenSelected == false) return;
    dt = dtClock.restart().asSeconds();
    float distance = sqrtf(((poolCue.getPosition().x + poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)) *
        ((poolCue.getPosition().x + poolCue.getRadius()) - (whiteBall->x + whiteBall->radius)) +
        ((poolCue.getPosition().y + poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)) * 
        ((poolCue.getPosition().y + poolCue.getRadius()) - (whiteBall->y + whiteBall->radius)));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(rad == 0) rad = whiteBall->radius + 10;
        mouseAim(whiteBall, event, rad);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (distance <= 200) { //alter distance of cue
            setPower(whiteBall, false);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (distance >= whiteBall->radius + 10) {
            setPower(whiteBall, true);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        state = MOVEMENT;
        rad = whiteBall->radius + 10;
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
            poolCue.setPosition(sf::Vector2f(ball->x + ball->radius - 10, ball->y - ball->radius - 10));
            line[0] = sf::Vertex(sf::Vector2f(poolCue.getPosition().x + poolCue.getRadius(), poolCue.getPosition().y + poolCue.getRadius()), sf::Color::Black);
            line[1] = sf::Vertex(sf::Vector2f(ball->x + ball->radius, ball->y + ball->radius), sf::Color::Black);
            ball->isSunk = false;
            state = PLAYERTURN;
        }
    }
}